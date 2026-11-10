/* Pit Stack, the firmware side's two calls (SUFST/Src/pit_stack.cpp). The game itself is pit_stack.h. */

#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* True while the game may be on screen: VCU present, tractive system off, all wheels stopped.
 * screen_select.c shows the Game screen only on dial position 8 and only while this is true. */
bool pit_stack_allowed(void);

/* Runs the game and draws it while the Game screen is showing. Call every pass of the UI loop. */
void pit_stack_tick(void);

#ifdef __cplusplus
}
#endif
