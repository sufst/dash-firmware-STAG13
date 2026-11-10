/* Start-up picture: how long the Splash screen stays up after power-up. The showing is done by
 * screen_select.c; this file only fetches the time from the EEZ Studio project. */

#include <stdint.h>

#include "eez-flow.h"
#include "screen_select.h"
#include "vars.h"

extern "C" int32_t splash_time_ms(void)
{
    /* splash_ms: EEZ Studio variable, milliseconds (5000). 0 = no picture. If this line doesn't compile, the
     * variable hasn't been added in EEZ Studio yet (Variables panel: name splash_ms, type integer) or the
     * project needs a Build. */
    return eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_SPLASH_MS).toInt32();
}
