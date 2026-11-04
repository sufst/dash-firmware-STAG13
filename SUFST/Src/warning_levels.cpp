/* Warning levels (0 = OK, 1 = warn, 2 = critical) for the dash's coloured panels, with hysteresis so a
 * reading sitting on a limit doesn't make the panel flicker. The limits themselves are the EEZ Studio
 * variables (inv_warn, motor_crit, soc_warn, ...), so they can still be changed in EEZ Studio.
 * Also here: soc_target, the SOC pace against an even plan for the race (see soc_target.h). */

#include <stdint.h>

#include "eez-flow.h"
#include "soc_target.h"
#include "vars.h"

/* A warning switches on at its limit but only switches off once the reading is this far back past it */
#define TEMP_HYSTERESIS_C 1.0
#define SOC_HYSTERESIS_PCT 2.0 /* SOC arrives in 0.5% steps and is rounded for display, so needs more */

static double global(enum FlowGlobalVariables index)
{
    return eez::flow::getGlobalVariable(index).toDouble();
}

/* Level for a reading where higher is worse */
static int32_t level_rising(int32_t previous, double value, double warn, double crit, double hysteresis)
{
    if (value >= crit || (previous == 2 && value > crit - hysteresis))
    {
        return 2;
    }
    if (value >= warn || (previous >= 1 && value > warn - hysteresis))
    {
        return 1;
    }
    return 0;
}

static double max4(double a, double b, double c, double d)
{
    double m = a > b ? a : b;
    m = m > c ? m : c;
    return m > d ? m : d;
}

extern "C" int32_t get_var_inv_level()
{
    static int32_t level = 0;
    double temp = max4(get_var_pm100_module_a(), get_var_pm100_module_b(),
                       get_var_pm100_module_c(), get_var_pm100_gate_driver_board());
    level = level_rising(level, temp, global(FLOW_GLOBAL_VARIABLE_INV_WARN),
                         global(FLOW_GLOBAL_VARIABLE_INV_CRIT), TEMP_HYSTERESIS_C);
    return level;
}

extern "C" int32_t get_var_motor_level()
{
    static int32_t level = 0;
    level = level_rising(level, get_var_pm100_motor_temperature(), global(FLOW_GLOBAL_VARIABLE_MOTOR_WARN),
                         global(FLOW_GLOBAL_VARIABLE_MOTOR_CRIT), TEMP_HYSTERESIS_C);
    return level;
}

extern "C" int32_t get_var_batt_level()
{
    static int32_t level = 0;
    level = level_rising(level, get_var_bms_high_temperature(), global(FLOW_GLOBAL_VARIABLE_BATT_WARN),
                         global(FLOW_GLOBAL_VARIABLE_BATT_CRIT), TEMP_HYSTERESIS_C);
    return level;
}

/* SOC is worse when lower: negate everything so the same rule applies */
extern "C" int32_t get_var_soc_level()
{
    static int32_t level = 0;
    level = level_rising(level, -get_var_bms_pack_soc(), -global(FLOW_GLOBAL_VARIABLE_SOC_WARN),
                         -global(FLOW_GLOBAL_VARIABLE_SOC_CRIT), SOC_HYSTERESIS_PCT);
    return level;
}

/* SOC target for the Endurance screen's bar: SOC ahead (+) or behind (-) an even plan, in SOC points.
 * lap_number is read as laps COMPLETED and total_laps is the race length; both are EEZ Studio variables
 * (neither has a CAN source yet). total_laps <= 0 means "not set", and the screen hides the bar. */
extern "C" int32_t get_var_soc_target()
{
    return soc_target_pct(get_var_bms_pack_soc(), (int32_t)global(FLOW_GLOBAL_VARIABLE_LAP_NUMBER),
                          (int32_t)global(FLOW_GLOBAL_VARIABLE_TOTAL_LAPS));
}

extern "C" void set_var_inv_level(int32_t value) { (void)value; }
extern "C" void set_var_motor_level(int32_t value) { (void)value; }
extern "C" void set_var_batt_level(int32_t value) { (void)value; }
extern "C" void set_var_soc_level(int32_t value) { (void)value; }
extern "C" void set_var_soc_target(int32_t value) { (void)value; }
