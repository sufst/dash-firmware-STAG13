#include "tusb.h"

// OTG_HS peripheral → TinyUSB rhport 1
void OTG_HS_IRQHandler(void)
{
    tud_int_handler(1);
}