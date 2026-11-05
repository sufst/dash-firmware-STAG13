/* Lap counter: the lap number goes up by 1 every lap_length metres the car drives.
 *
 * Distance comes from the front wheel speeds the VCU broadcasts on CAN-S (Wheel_Speeds, m/s, every 20 ms),
 * added up over time. The fronts aren't driven, so wheelspin doesn't add distance.
 * lap_length is an EEZ Studio variable (metres): set it for each track in EEZ Studio's Variables panel,
 * next to total_laps. 0 switches the counter off.
 * lap_number is laps COMPLETED: 0 until the first lap_length is covered (also what the SOC target uses).
 * Distance starts from 0 each time the dash powers up.
 *
 * The maths is header-only so it can be tested on a PC; lap_counter.cpp is the firmware side. */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Called every pass of the UI loop (freertos.c), before ui_tick() */
void lap_counter_tick(void);

#ifdef __cplusplus
}
#endif

/* A UI-loop pass longer than this (e.g. while a screen is being built) only counts for this long */
#define LAP_MAX_STEP_MS 200U

/* Above this speed, a front wheel reading under half the other is treated as faulty (see below) */
#define LAP_FAULT_CHECK_MPS 5.0

/* Speed used for distance: the mean of the two front wheels, which is the speed of the middle of the car,
 * so it is right through corners too. If one front reads under half the other at speed (dead sensor, or a
 * wheel locking under braking) the faster one is used instead: even in the tightest FS hairpin the inside
 * front turns at about 75% of the outside one, so the 50% rule only catches faults. Negative reads as 0. */
static inline double lap_front_speed_mps(double fl, double fr)
{
    if (fl < 0.0)
    {
        fl = 0.0;
    }
    if (fr < 0.0)
    {
        fr = 0.0;
    }
    double hi = fl > fr ? fl : fr;
    double lo = fl > fr ? fr : fl;
    if (hi > LAP_FAULT_CHECK_MPS && lo < 0.5 * hi)
    {
        return hi;
    }
    return 0.5 * (fl + fr);
}

typedef struct
{
    double distance_m; /* since power-up */
    uint32_t last_ms;
    bool started;
} lap_odometer_t;

/* Adds the distance covered since the last call. now_ms is a millisecond clock (wrap-around is fine).
 * speed_valid false (no recent Wheel_Speeds frame) adds nothing, so a lost CAN-S link can't run away. */
static inline void lap_odometer_step(lap_odometer_t *odo, uint32_t now_ms, double speed_mps, bool speed_valid)
{
    if (odo->started && speed_valid)
    {
        uint32_t dt_ms = now_ms - odo->last_ms;
        if (dt_ms > LAP_MAX_STEP_MS)
        {
            dt_ms = LAP_MAX_STEP_MS;
        }
        odo->distance_m += speed_mps * (double)dt_ms / 1000.0;
    }
    odo->last_ms = now_ms;
    odo->started = true;
}

/* Whole laps in distance_m; 0 if lap_length_m isn't set (<= 0) */
static inline int32_t lap_laps_completed(double distance_m, double lap_length_m)
{
    if (lap_length_m <= 0.0 || distance_m <= 0.0)
    {
        return 0;
    }
    return (int32_t)(distance_m / lap_length_m);
}
