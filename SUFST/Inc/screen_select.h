#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Shows the screen for the VCU's current drive mode (set by the dash dial). Call from the UI task. */
void screen_select_tick(void);

#ifdef __cplusplus
}
#endif
