/* Dash-side CAN health, exposed to EEZ Studio as native variables for the debug screen */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "main.h"
#include "can.h"
#include "can_t.h"
#include "dash_diag.h"

/* VCU_State is broadcast periodically; half a second of silence is treated as a lost link */
#define VCU_LINK_TIMEOUT_MS 500U

static volatile uint32_t rx_dropped = 0;
static volatile uint32_t last_vcu_state_tick = 0;
static volatile bool vcu_state_seen = false;

void dash_diag_note_rx(bool is_bus_t, uint32_t id)
{
    if (is_bus_t && (id == CAN_T_VCU_STATE_FRAME_ID))
    {
        last_vcu_state_tick = HAL_GetTick();
        vcu_state_seen = true;
    }
}

void dash_diag_note_rx_dropped(void)
{
    rx_dropped++;
}

/* Formats the bxCAN error status register as e.g. "OK 0/0", "PASSIVE 130/2" or "BUS OFF" */
static const char *format_bus_status(CAN_HandleTypeDef *hcan, char *buf, size_t size)
{
    uint32_t esr = hcan->Instance->ESR;
    unsigned tec = (unsigned)((esr & CAN_ESR_TEC) >> CAN_ESR_TEC_Pos);
    unsigned rec = (unsigned)((esr & CAN_ESR_REC) >> CAN_ESR_REC_Pos);

    if (esr & CAN_ESR_BOFF)
    {
        snprintf(buf, size, "BUS OFF");
    }
    else
    {
        const char *state = (esr & CAN_ESR_EPVF) ? "PASSIVE" : (esr & CAN_ESR_EWGF) ? "WARN" : "OK";
        snprintf(buf, size, "%s %u/%u", state, tec, rec);
    }
    return buf;
}

const char *get_var_can_s_status(void)
{
    static char buf[24];
    return format_bus_status(&hcan1, buf, sizeof(buf));
}

void set_var_can_s_status(const char *value)
{
    (void)value;
}

const char *get_var_can_t_status(void)
{
    static char buf[24];
    return format_bus_status(&hcan2, buf, sizeof(buf));
}

void set_var_can_t_status(const char *value)
{
    (void)value;
}

int32_t get_var_can_rx_dropped(void)
{
    return (int32_t)rx_dropped;
}

void set_var_can_rx_dropped(int32_t value)
{
    (void)value;
}

bool get_var_vcu_link_ok(void)
{
    return vcu_state_seen && ((HAL_GetTick() - last_vcu_state_tick) < VCU_LINK_TIMEOUT_MS);
}

void set_var_vcu_link_ok(bool value)
{
    (void)value;
}
