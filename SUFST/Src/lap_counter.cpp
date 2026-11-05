/* Lap counter, firmware side: turns the front wheel speeds into distance and writes lap_number for the
 * screens. How it works, and where lap_length is set, is described in lap_counter.h. */

#include <stdint.h>

#include "main.h"

#include "dash_diag.h"
#include "eez-flow.h"
#include "lap_counter.h"
#include "vars.h"

extern "C" void lap_counter_tick(void)
{
    static lap_odometer_t odo = {0.0, 0, false};
    static int32_t shown_laps = -1;

    bool fresh = dash_diag_wheel_speeds_fresh();
    double speed = fresh ? lap_front_speed_mps(get_var_wheel_fl_speed(), get_var_wheel_fr_speed()) : 0.0;
    lap_odometer_step(&odo, HAL_GetTick(), speed, fresh);

    /* lap_length: EEZ Studio variable, metres. If this line doesn't compile, the variable hasn't been added
     * in EEZ Studio yet (Variables panel: name lap_length, type integer) or the project needs a Build. */
    double lap_length_m = eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_LAP_LENGTH).toDouble();

    int32_t laps = lap_laps_completed(odo.distance_m, lap_length_m);
    if (laps != shown_laps)
    {
        eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_LAP_NUMBER, eez::IntegerValue(laps));
        shown_laps = laps;
    }
}
