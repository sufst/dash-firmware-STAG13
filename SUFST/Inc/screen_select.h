#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Shows the Splash screen (picture + turn-on instructions) at power-up, then the screen for the VCU's current
 * drive mode (set by the dash dial). The rules are at the top of screen_select.c. Call from the UI task. */
void screen_select_tick(void);

/* How long the Splash screen stays when it is not waiting for the turn-on instructions, ms: the EEZ Studio
 * variable splash_ms (splash.cpp) */
int32_t splash_time_ms(void);

#ifdef __cplusplus
}
#endif
