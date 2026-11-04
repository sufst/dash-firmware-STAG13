/* Auto generated: Do not edit directly, instead add signals in Codegen/signal_mapping.yaml or update Codegen/can_rx_handlers.h.j2 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void can_t_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length);
void can_s_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length);

int32_t get_raw_vcu_ctrl_state(void);
int32_t get_raw_vcu_current_mode(void);
int32_t get_raw_vcu_requested_mode(void);
int32_t get_raw_vcu_lc_state(void);
int32_t get_raw_vcu_lc_fault(void);
int32_t get_raw_pm100_vsm_state(void);

#ifdef __cplusplus
}
#endif