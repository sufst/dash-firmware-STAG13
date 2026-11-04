import os
import json
import uuid
import yaml
import cantools
import cantools.database
from jinja2 import Environment, FileSystemLoader

# Configuration paths
REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
YAML_PATH = os.path.join(REPO_ROOT, 'Codegen/signal_mapping.yaml')
JINJA_TEMPLATE_PATH = os.path.join(REPO_ROOT, 'Codegen/can_rx_handlers.c.j2')
JINJA_HEADER_TEMPLATE_PATH = os.path.join(REPO_ROOT, 'Codegen/can_rx_handlers.h.j2')
EEZ_PROJECT_PATH = os.path.join(REPO_ROOT, 'eez-Stag12/Stag12.eez-project')
OUTPUT_C_PATH = os.path.join(REPO_ROOT, 'SUFST/Src/can_rx_handlers.c')
OUTPUT_H_PATH = os.path.join(REPO_ROOT, 'SUFST/Inc/can_rx_handlers.h')

DBC_PATHS = {
    "CAN_T": os.path.join(REPO_ROOT, "SUFST/Middlewares/can-defs/dbc/CAN-T.dbc"),
    "CAN_S": os.path.join(REPO_ROOT, "SUFST/Middlewares/can-defs/dbc/CAN-S.dbc"),
}

BOOLEAN_UNIT_ALIASES = {"off/on", "bool", "boolean", "bit"}

ZERO_LITERALS = {
    "double": "0.0",
    "float": "0.0f",
    "int32_t": "0",
    "bool": "false",
}

# EEZ Studio's variable "defaultValue" is an expression string, not a raw
# literal -- a "string" default must itself be a quoted string expression
# (e.g. the JSON value "\"\""), otherwise EEZ Studio's checker rejects it
# with "not a string". Other types are left as bare numeric/boolean literals.
DEFAULT_VALUES = {
    "string": '""',
    "boolean": "false",
}

INT32_MIN, INT32_MAX = -2147483648, 2147483647


def generate_uuid():
    """Generates a standard UUID for EEZ Studio objects."""
    return str(uuid.uuid4())


def c_escape(text):
    """Escapes a string for embedding as a C string literal body."""
    return text.replace('\\', '\\\\').replace('"', '\\"')


def load_dbc_databases(bus_names):
    """Loads a cantools Database per bus, keyed by bus name."""
    databases = {}
    for bus in bus_names:
        if bus not in DBC_PATHS:
            raise ValueError(
                f"No DBC configured for bus '{bus}'. Add it to DBC_PATHS in main.py. "
                f"Known buses: {sorted(DBC_PATHS)}"
            )
        path = DBC_PATHS[bus]
        if not os.path.exists(path):
            raise FileNotFoundError(f"DBC for bus '{bus}' not found at {path}")
        try:
            databases[bus] = cantools.database.load_file(path)
        except Exception as e:
            raise RuntimeError(f"Failed to parse DBC for bus '{bus}' ({path}): {e}") from e
    return databases


def find_signal(db, message_name, signal_name):
    """Case-insensitive message/signal lookup in a cantools Database."""
    message = next((m for m in db.messages if m.name.upper() == message_name.upper()), None)
    if message is None:
        available = sorted(m.name for m in db.messages)
        raise ValueError(f"Message '{message_name}' not found in DBC. Available: {available}")

    signal = next((s for s in message.signals if s.name.upper() == signal_name.upper()), None)
    if signal is None:
        available = sorted(s.name for s in message.signals)
        raise ValueError(
            f"Signal '{signal_name}' not found in message '{message.name}'. Available: {available}"
        )
    return signal


def signal_physical_range(signal):
    """Returns (min, max) for a signal's physical value, preferring the DBC-declared range."""
    if signal.minimum is not None and signal.maximum is not None:
        return signal.minimum, signal.maximum

    if signal.is_signed:
        raw_min, raw_max = -(2 ** (signal.length - 1)), 2 ** (signal.length - 1) - 1
    else:
        raw_min, raw_max = 0, 2 ** signal.length - 1

    a = raw_min * signal.scale + signal.offset
    b = raw_max * signal.scale + signal.offset
    return min(a, b), max(a, b)


def classify_signal_type(signal):
    """Classifies a cantools Signal into the EEZ/C type used to represent it.

    Returns a dict with eez_type, backing_c_type, accessor_c_type and choices
    (None, or a sorted [(raw_value, escaped_label), ...] list for "string" types).
    """
    if signal.choices is not None:
        choices = sorted(
            (value, c_escape(str(label))) for value, label in signal.choices.items()
        )
        return {
            "eez_type": "string",
            "backing_c_type": "int32_t",
            "accessor_c_type": "const char *",
            "choices": choices,
        }

    if signal.is_float:
        c_type = "float" if signal.length <= 32 else "double"
        return {"eez_type": c_type, "backing_c_type": c_type, "accessor_c_type": c_type, "choices": None}

    if signal.length == 1:
        return {"eez_type": "boolean", "backing_c_type": "bool", "accessor_c_type": "bool", "choices": None}

    unit = (signal.unit or "").strip().lower()
    if unit in BOOLEAN_UNIT_ALIASES:
        if signal.minimum is not None and signal.maximum is not None \
                and 0 <= signal.minimum and signal.maximum <= 1:
            return {"eez_type": "boolean", "backing_c_type": "bool", "accessor_c_type": "bool", "choices": None}

    is_integral = signal.scale == int(signal.scale) and signal.offset == int(signal.offset)
    if is_integral:
        phys_min, phys_max = signal_physical_range(signal)
        if phys_min >= INT32_MIN and phys_max <= INT32_MAX:
            return {"eez_type": "integer", "backing_c_type": "int32_t", "accessor_c_type": "int32_t", "choices": None}

    return {"eez_type": "double", "backing_c_type": "double", "accessor_c_type": "double", "choices": None}


def multiplexer_guard_expr(signal):
    """Returns a C boolean expression guarding a multiplexed signal's decode
    (e.g. "payload.pdm_in_voltage_compound_id == 1"), or None if the signal
    isn't multiplexed.

    A multiplexed signal only occupies its bit position for specific values of
    its selector signal; other mux groups reuse those same bits for unrelated
    signals. cantools' generated unpack() only ever writes the struct field
    when the selector matches, so decoding it unconditionally reads whatever
    stale/uninitialized value is left in the struct the rest of the time.
    """
    if signal.multiplexer_ids is None:
        return None

    selector_field = signal.multiplexer_signal.lower()
    comparisons = [f"payload.{selector_field} == {mux_id}" for mux_id in sorted(signal.multiplexer_ids)]
    if len(comparisons) == 1:
        return comparisons[0]
    return "(" + " || ".join(comparisons) + ")"


def resolve_target(target, sig_name, classification):
    """Returns (variable path, round_to_int) for a signal_mapping.yaml entry, which is
    either a bare variable name or a {name, type} mapping."""
    if isinstance(target, str):
        return target, False

    if not isinstance(target, dict) or "name" not in target:
        raise ValueError(f"Mapping for signal '{sig_name}' must be a variable name or {{name, type}}")

    requested_type = target.get("type")
    if requested_type is None or requested_type == classification["eez_type"]:
        return target["name"], False
    if requested_type == "integer" and classification["eez_type"] in ("double", "float"):
        return target["name"], True
    raise ValueError(
        f"Signal '{sig_name}' is {classification['eez_type']!r}; type override {requested_type!r} "
        "is not supported (only integer for scaled numeric signals)."
    )


def build_resolved_buses(yaml_data, databases):
    """Resolves signal_mapping.yaml against the loaded DBCs into the template context,
    classifying each signal's type exactly once."""
    buses = []
    for bus_name, messages in yaml_data.items():
        db = databases[bus_name]
        bus_entry = {"name": bus_name, "messages": []}
        for msg_name, signals in messages.items():
            # optional "_timeout_ms": getters report no data once the message goes quiet
            msg_entry = {"name": msg_name, "signals": [], "timeout_ms": signals.get("_timeout_ms")}
            for sig_name, target in signals.items():
                if sig_name.startswith("_"):
                    continue
                cantools_signal = find_signal(db, msg_name, sig_name)
                classification = classify_signal_type(cantools_signal)
                path, round_to_int = resolve_target(target, sig_name, classification)
                if round_to_int:
                    classification = dict(classification, eez_type="integer", accessor_c_type="int32_t")
                msg_entry["signals"].append({
                    "name": sig_name,
                    "flat_name": path.replace('.', '_'),
                    "eez_type": classification["eez_type"],
                    "backing_c_type": classification["backing_c_type"],
                    "accessor_c_type": classification["accessor_c_type"],
                    "choices": classification["choices"],
                    "zero_literal": ZERO_LITERALS[classification["backing_c_type"]],
                    "mux_guard_expr": multiplexer_guard_expr(cantools_signal),
                    "round_to_int": round_to_int,
                })
            bus_entry["messages"].append(msg_entry)
        buses.append(bus_entry)
    return buses


def build_eez_flat_variables(buses, eez_data):
    """Injects/updates flat, native global variables in the EEZ project from resolved signal types."""
    eez_data.setdefault("variables", {}).setdefault("globalVariables", [])
    global_vars = eez_data["variables"]["globalVariables"]

    for bus in buses:
        for msg in bus["messages"]:
            for sig in msg["signals"]:
                existing_var = next((v for v in global_vars if v.get("name") == sig["flat_name"]), None)
                default_value = DEFAULT_VALUES.get(sig["eez_type"], "0")

                if existing_var is None:
                    global_vars.append({
                        "objID": generate_uuid(),
                        "name": sig["flat_name"],
                        "type": sig["eez_type"],
                        "defaultValue": default_value,
                        "native": True
                    })
                else:
                    if not existing_var.get("native"):
                        print(f"NOTE: '{sig['flat_name']}' was not native; switching it to native so it reads from CAN.")
                        existing_var["native"] = True
                    if existing_var.get("type") != sig["eez_type"]:
                        print(
                            f"WARNING: '{sig['flat_name']}' type changed "
                            f"{existing_var.get('type')!r} -> {sig['eez_type']!r}; updating in place. "
                            "Re-check any EEZ Studio widgets/expressions bound to this variable."
                        )
                        existing_var["type"] = sig["eez_type"]
                    if existing_var.get("defaultValue") != default_value:
                        existing_var["defaultValue"] = default_value


def main():
    # 1. Load the YAML mapping
    if not os.path.exists(YAML_PATH):
        print(f"Error: YAML mapping file not found at {YAML_PATH}")
        return

    with open(YAML_PATH, 'r') as f:
        mapping_data = yaml.safe_load(f)

    # 2. Load DBCs and resolve each signal's type
    databases = load_dbc_databases(mapping_data.keys())
    buses = build_resolved_buses(mapping_data, databases)

    # 3. Update EEZ Project JSON
    if os.path.exists(EEZ_PROJECT_PATH):
        with open(EEZ_PROJECT_PATH, 'r') as f:
            eez_data = json.load(f)

        build_eez_flat_variables(buses, eez_data)

        with open(EEZ_PROJECT_PATH, 'w') as f:
            json.dump(eez_data, f, indent=2)
        print(f"Updated {EEZ_PROJECT_PATH} successfully.")
    else:
        print(f"Warning: {EEZ_PROJECT_PATH} not found. Skipping UI project update.")

    # 4. Render Jinja2 Templates
    env = Environment(loader=FileSystemLoader(os.path.dirname(JINJA_TEMPLATE_PATH)))

    c_template = env.get_template(os.path.basename(JINJA_TEMPLATE_PATH))
    with open(OUTPUT_C_PATH, 'w') as f:
        f.write(c_template.render(buses=buses))
    print(f"Generated {OUTPUT_C_PATH} successfully.")

    h_template = env.get_template(os.path.basename(JINJA_HEADER_TEMPLATE_PATH))
    with open(OUTPUT_H_PATH, 'w') as f:
        f.write(h_template.render(buses=buses))
    print(f"Generated {OUTPUT_H_PATH} successfully.")

if __name__ == "__main__":
    main()
