#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Called from the CAN RX interrupt for every frame received */
void dash_diag_note_rx(bool is_bus_t, uint32_t id);

/* Called from the CAN RX interrupt when the RX queue was full and the frame was lost */
void dash_diag_note_rx_dropped(void);

#ifdef __cplusplus
}
#endif
