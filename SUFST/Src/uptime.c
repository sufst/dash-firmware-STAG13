#include <stdint.h>
#include <stdio.h>

#include "main.h"

const char * get_var_uptime_str(void)
{
    static char buf[9]; /* "HH:MM:SS\0" */

    uint32_t total_seconds = HAL_GetTick() / 1000U;
    uint32_t hours = (total_seconds / 3600U) % 100U; /* clamp to 2 digits */
    uint32_t minutes = (total_seconds / 60U) % 60U;
    uint32_t seconds = total_seconds % 60U;

    snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu",
              (unsigned long) hours, (unsigned long) minutes, (unsigned long) seconds);

    return buf;
}

void set_var_uptime_str(const char * value)
{
    (void) value;
}

/* Whole seconds since power-on, for timed things on screen (e.g. rotating sponsor logos) */
int32_t get_var_uptime_s(void)
{
    return (int32_t) (HAL_GetTick() / 1000U);
}

void set_var_uptime_s(int32_t value)
{
    (void) value;
}
