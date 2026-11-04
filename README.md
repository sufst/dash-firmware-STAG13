# Dashboard Firmware (Stag 13)

Started from `dash-firmware-STAG12` (Endurance dash, state of 4 Nov 2026). The folder and project names (`eez-Stag12`, `Stag12.eez-project`) are unchanged so the build files still match; rename them together when ready.

After cloning, run `git submodule update --init` (CAN definitions and LVGL are submodules).

Dashboard firmware for a STM32F746ZGT connected to two CAN buses (CAN-T and CAN-S, with definitions [here](https://github.com/sufst/can-defs)), using EEZ Studio + LVGL for rendering. 

## Updating the UI
Open `eez-Stag12/Stag12.eez-project` in EEZ Studio

## Adding signals
1. Open `Codegen/signal_mapping.yaml`
2. Add the CAN frames and signals you want to be accessible inside EEZ studio
3. Make sure EEZ studio is *closed*, then:
4. Run the generation: `cd Codegen && uv sync && uv run main.py` ([uv installation guide](https://docs.astral.sh/uv/#installation))
5. Open the project inside EEZ studio, hit check then build, save the project
6. Check the project builds properly (see below)

## To build and flash
- To build: `make`
- To flash with the st-link connected: `make flash`
