/* SOC target: how far the pack is ahead of (+) or behind (-) an even energy plan for the race.
 *
 * The plan spends the pack evenly across the race, from SOC_PLAN_START_PCT at the start to
 * SOC_PLAN_FINISH_PCT at the end:  planned SOC = start - (start - finish) * laps_done / total_laps.
 * Target = actual SOC - planned SOC, in percentage points (same as: planned SOC used - actual SOC used).
 *   10 laps, 1 done, 11 % used (SOC 89): plan 90 -> -1  (behind: using too much)
 *   10 laps, 4 done, 65 % left:          plan 60 -> +5  (ahead: SOC to spare)
 * Header-only so it can be unit tested on a PC without the EEZ headers. */
#pragma once

#include <stdint.h>

#define SOC_PLAN_START_PCT 100.0
#define SOC_PLAN_FINISH_PCT 0.0

/* Returns 0 if total_laps is not set (<= 0); laps_done is held to 0..total_laps */
static inline int32_t soc_target_pct(int32_t soc_pct, int32_t laps_done, int32_t total_laps)
{
    if (total_laps <= 0)
    {
        return 0;
    }
    if (laps_done < 0)
    {
        laps_done = 0;
    }
    if (laps_done > total_laps)
    {
        laps_done = total_laps;
    }
    double planned = SOC_PLAN_START_PCT -
                     (SOC_PLAN_START_PCT - SOC_PLAN_FINISH_PCT) * (double)laps_done / (double)total_laps;
    double target = (double)soc_pct - planned;
    return (int32_t)(target < 0 ? target - 0.5 : target + 0.5); /* round half away from zero */
}
