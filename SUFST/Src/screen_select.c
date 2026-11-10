/* Picks the EEZ Studio screen: at power-up the Splash screen (picture + turn-on instructions), then the
 * screen for the VCU's current drive mode (VCU_State.VCU_Current_Mode).
 *
 * How long the Splash screen stays:
 *   - VCU talking, dial on a driving screen (Endurance, Skidpad, Accel): for exactly as long as the turn-on
 *     instructions have something to say. The moment the driver has completed them (R2D pressed, VCU state
 *     "TS On") the driving screen shows. There is no minimum time: if the dash restarts while the car is
 *     already driving, the driving screen is back as soon as the first VCU_State frame arrives.
 *   - VCU talking, dial on Dyno, Debug, Sponsors or Game: for splash_ms (EEZ Studio variable, 5000),
 *     whatever the car is doing (Debug is needed exactly when the car will not start, and the game only
 *     exists with the tractive system off)
 *   - no VCU on the bus (dash alone on the bench, or the VCU not up yet): until splash_ms, or until the VCU
 *     starts talking and one of the rules above applies
 * Once it has gone it does not come back until the next power-up; the driving screens have their own
 * start-up instructions for after that. */

#include <stdint.h>

#include "main.h"

#include "can_rx_handlers.h"
#include "pit_stack_fw.h"
#include "screen_select.h"
#include "screens.h"
#include "ui.h"
#include "vars.h"

/* Mode numbers as sent by the VCU (see VCU_Current_Mode in CAN-T.dbc); the dial has 12 positions */
static enum ScreensEnum screen_for_mode(int32_t mode)
{
    switch (mode)
    {
    case 1:  return SCREEN_ID_MAIN;    /* Endurance */
    case 2:  return SCREEN_ID_SKIDPAD; /* Max */
    case 3:  return SCREEN_ID_ACCEL;   /* Launch_Ctrl */
    case 6:  return SCREEN_ID_DYNO;    /* Remote_Ctrl */
    case 7:  return SCREEN_ID_DEBUG;    /* Undefined */
    case 8:                             /* Undefined: the game, but only with the car parked and dead */
        return pit_stack_allowed() ? SCREEN_ID_GAME : SCREEN_ID_DEBUG;
    case 9:  return SCREEN_ID_SPONSORS; /* Undefined: car on show */
    case 10:
    case 11:
    case 12: return SCREEN_ID_DEBUG;   /* Inverter_Prog, until it has its own screen */
    default: return SCREEN_ID_MAIN;    /* Crawl, Reverse and no VCU data yet */
    }
}

/* True while the turn-on instructions have something to say. These are the VCU states the instructions text
 * covers (splash_instructions on the Splash screen, same as startup_instructions on Main): keep them in step.
 * Only meaningful while the VCU is talking (get_var_vcu_link_ok(), which goes by the same VCU_State frame
 * that carries this state). */
static uint8_t instructions_pending(void)
{
    switch (get_raw_vcu_ctrl_state())
    {
    case 0: /* TS Button Wait: "Press TS_ON (left)" */
    case 1: /* Wait Neg AIR:   "Precharging..." */
    case 2: /* Precharge Wait: "Precharging..." */
    case 3: /* R2D Wait:       "Press R2D (right)" */
    case 8: /* TS Run Fault:   "Fault: Press TS_OFF (left)" */
        return 1;
    default:
        return 0;
    }
}

static uint8_t is_driving_screen(enum ScreensEnum screen)
{
    return screen == SCREEN_ID_MAIN || screen == SCREEN_ID_SKIDPAD || screen == SCREEN_ID_ACCEL;
}

void screen_select_tick(void)
{
    static enum ScreensEnum current = SCREEN_ID_MAIN;
    static uint32_t start_ms;
    static uint8_t started = 0;
    static uint8_t splash_over = 0;

    if (!started)
    {
        start_ms = HAL_GetTick(); /* splash_ms is timed from the first frame drawn */
        started = 1;
    }
    enum ScreensEnum wanted = screen_for_mode(get_raw_vcu_current_mode());

    if (!splash_over)
    {
        int32_t splash_ms = splash_time_ms();
        if (splash_ms <= 0)
        {
            splash_over = 1; /* switched off in EEZ Studio */
        }
        else if (get_var_vcu_link_ok() && is_driving_screen(wanted))
        {
            splash_over = !instructions_pending(); /* gone the moment the instructions are complete */
        }
        else
        {
            splash_over = (HAL_GetTick() - start_ms) >= (uint32_t)splash_ms;
        }
    }
    if (!splash_over)
    {
        wanted = SCREEN_ID_SPLASH;
    }

    if (wanted != current)
    {
        eez_flow_set_screen(wanted, LV_SCR_LOAD_ANIM_NONE, 0, 0);
        current = wanted;
    }
}
