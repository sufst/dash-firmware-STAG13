#ifndef USB_MODE_H
#define USB_MODE_H

#include <stdbool.h>

// Set at boot based on button state, read-only after that.
// true  = MSC mode  : SD card exposed to host, no FatFS access to STM32
// false = normal mode: FatFS active, SD card never exposed to host
extern bool msc_mode;

#endif /* USB_MODE_H */