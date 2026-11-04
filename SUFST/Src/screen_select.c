/* Picks the EEZ Studio screen from the VCU's current drive mode (VCU_State.VCU_Current_Mode) */

#include <stdint.h>

#include "can_rx_handlers.h"
#include "screen_select.h"
#include "screens.h"
#include "ui.h"

/* Mode numbers as sent by the VCU (see VCU_Current_Mode in CAN-T.dbc); the dial has 12 positions */
static enum ScreensEnum screen_for_mode(int32_t mode)
{
    switch (mode)
    {
    case 1:  return SCREEN_ID_MAIN;    /* Endurance */
    case 2:  return SCREEN_ID_SKIDPAD; /* Max */
    case 3:  return SCREEN_ID_ACCEL;   /* Launch_Ctrl */
    case 6:  return SCREEN_ID_DYNO;    /* Remote_Ctrl */
    case 7:
    case 8:  return SCREEN_ID_DEBUG;    /* Undefined */
    case 9:  return SCREEN_ID_SPONSORS; /* Undefined: car on show */
    case 10:
    case 11:
    case 12: return SCREEN_ID_DEBUG;   /* Inverter_Prog, until it has its own screen */
    default: return SCREEN_ID_MAIN;    /* Crawl, Reverse and no VCU data yet */
    }
}

void screen_select_tick(void)
{
    static enum ScreensEnum current = SCREEN_ID_MAIN;
    enum ScreensEnum wanted = screen_for_mode(get_raw_vcu_current_mode());

    if (wanted != current)
    {
        eez_flow_set_screen(wanted, LV_SCR_LOAD_ANIM_NONE, 0, 0);
        current = wanted;
    }
}
