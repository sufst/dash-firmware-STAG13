#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Shows the start-up picture (Splash screen) for the first splash_ms after power-up, then the screen for the
 * VCU's current drive mode (set by the dash dial). Call from the UI task. */
void screen_select_tick(void);

/* How long the start-up picture stays up, ms: the EEZ Studio variable splash_ms (splash.cpp) */
int32_t splash_time_ms(void);

#ifdef __cplusplus
}
#endif
