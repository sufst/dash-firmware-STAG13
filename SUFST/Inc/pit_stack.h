/* Pit Stack: a block-stacking game for the dash, for when the car is parked with the tractive system off.
 *
 * Blocks of 2 to 4 squares fall into a well 12 wide and 16 high. A full row disappears and scores 1.
 * The game ends when a new block has no room. It gets faster every 8 rows.
 *
 * Played with the car's own controls (the dash has no buttons):
 *     steering wheel   where the block is: wheel left = block at the left wall, wheel right = right wall
 *     brake pedal      turn the block (one turn per press); also starts, resumes and restarts the game
 *     throttle pedal   drop the block fast while it is held
 *
 * This file is the whole game with no hardware in it, so it also builds on a PC (C:\dashwork\sim\test_pit_stack.c).
 * The firmware side (reading the pedals, when the game is allowed, drawing) is SUFST/Src/pit_stack.cpp. */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define PS_W 12 /* well width, squares */
#define PS_H 16 /* well height, squares */

#define PS_PIECES 8
#define PS_COLOURS 4 /* squares carry a colour number 1..PS_COLOURS; 0 = empty */

#define PS_MOVE_MS 35       /* the block follows the steering wheel one column per this long */
#define PS_FALL_SLOW_MS 600 /* time per row at the start */
#define PS_FALL_STEP_MS 40  /* faster by this much... */
#define PS_ROWS_PER_LEVEL 8 /* ...every this many rows */
#define PS_FALL_FAST_MS 120 /* fastest it gets by itself */
#define PS_FALL_DROP_MS 30  /* time per row with the throttle down */
#define PS_RESTART_MS 1000  /* after game over, brake presses are ignored for this long */

typedef enum
{
    PS_READY,   /* nothing started yet */
    PS_PLAYING,
    PS_PAUSED,  /* the game screen went away mid-game */
    PS_OVER
} ps_state_t;

typedef struct
{
    uint8_t cell[PS_H][PS_W]; /* landed squares: 0 empty, else colour number */
    uint16_t mask;            /* falling block: bit (y * 4 + x) set = square at x, y of its 4 x 4 box */
    uint8_t colour;
    int8_t x, y;              /* where the top left of the block's box is in the well */
    uint8_t state;            /* ps_state_t */
    bool brake_was_down;
    bool drop_armed;          /* throttle has been lifted since the last block landed */
    bool changed;             /* something to redraw; the drawing side clears it */
    uint32_t rows, best;
    uint32_t last_fall_ms, last_move_ms, over_ms;
    uint32_t rng;
} ps_game_t;

/* The blocks, in their 4 x 4 box (top left filled first): 2, 3, 3, 4, 4, 4, 4, 4 squares */
static const uint16_t ps_shapes[PS_PIECES] = {
    0x0003, /* ##            */
    0x0007, /* ###           */
    0x0013, /* ## / #        */
    0x000F, /* ####          */
    0x0033, /* ## / ##       */
    0x0027, /* ### / .#      */
    0x0311, /* # / # / ##    */
    0x0036, /* .## / ##      */
};

static inline bool ps_mask_at(uint16_t mask, int x, int y) { return (mask >> (y * 4 + x)) & 1u; }

/* Quarter turn clockwise, pushed back into the top left of the box */
static inline uint16_t ps_rotate(uint16_t mask)
{
    uint16_t out = 0;
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (ps_mask_at(mask, x, y))
                out |= (uint16_t)(1u << (x * 4 + (3 - y)));
    while (!(out & 0x000F))
        out >>= 4; /* up */
    while (!(out & 0x1111))
        out >>= 1; /* left */
    return out;
}

static inline int ps_mask_width(uint16_t mask)
{
    int w = 0;
    for (int x = 0; x < 4; x++)
        if (mask & (0x1111u << x))
            w = x + 1;
    return w;
}

/* True if the block can't be at x, y: outside the well or on a landed square */
static inline bool ps_blocked(const ps_game_t *g, uint16_t mask, int x, int y)
{
    for (int by = 0; by < 4; by++)
        for (int bx = 0; bx < 4; bx++)
            if (ps_mask_at(mask, bx, by))
            {
                int cx = x + bx, cy = y + by;
                if (cx < 0 || cx >= PS_W || cy < 0 || cy >= PS_H || g->cell[cy][cx])
                    return true;
            }
    return false;
}

/* The column the steering wheel is asking for. steer: 0 = full left, 1 = full right */
static inline int ps_target_column(uint16_t mask, float steer)
{
    int room = PS_W - ps_mask_width(mask);
    if (!(steer > 0.0f))
        steer = 0.0f; /* also catches NaN */
    if (steer > 1.0f)
        steer = 1.0f;
    return (int)(steer * (float)room + 0.5f);
}

static inline uint32_t ps_fall_ms(const ps_game_t *g)
{
    uint32_t faster = (g->rows / PS_ROWS_PER_LEVEL) * PS_FALL_STEP_MS;
    return (faster >= PS_FALL_SLOW_MS - PS_FALL_FAST_MS) ? PS_FALL_FAST_MS : PS_FALL_SLOW_MS - faster;
}

static inline void ps_new_block(ps_game_t *g, uint32_t now_ms, float steer)
{
    g->rng = g->rng * 1664525u + 1013904223u;
    uint32_t pick = (g->rng >> 16) % PS_PIECES;
    g->mask = ps_shapes[pick];
    g->colour = (uint8_t)(pick % PS_COLOURS + 1);
    g->x = (int8_t)ps_target_column(g->mask, steer);
    g->y = 0;
    g->last_fall_ms = now_ms;
    g->drop_armed = false;
    if (ps_blocked(g, g->mask, g->x, g->y))
    {
        g->state = PS_OVER;
        g->over_ms = now_ms;
    }
}

static inline void ps_start(ps_game_t *g, uint32_t now_ms, float steer)
{
    memset(g->cell, 0, sizeof(g->cell));
    g->rows = 0;
    g->rng ^= now_ms * 2654435761u; /* when the brake was pressed decides the blocks */
    g->state = PS_PLAYING;
    ps_new_block(g, now_ms, steer);
}

/* The falling block lands: its squares join the well, full rows go, the next block comes */
static inline void ps_land(ps_game_t *g, uint32_t now_ms, float steer)
{
    for (int by = 0; by < 4; by++)
        for (int bx = 0; bx < 4; bx++)
            if (ps_mask_at(g->mask, bx, by))
                g->cell[g->y + by][g->x + bx] = g->colour;

    int to = PS_H - 1;
    for (int from = PS_H - 1; from >= 0; from--)
    {
        bool full = true;
        for (int x = 0; x < PS_W; x++)
            full = full && g->cell[from][x];
        if (full)
        {
            g->rows++;
            continue;
        }
        if (to != from)
            memcpy(g->cell[to], g->cell[from], PS_W);
        to--;
    }
    for (; to >= 0; to--)
        memset(g->cell[to], 0, PS_W);

    if (g->rows > g->best)
        g->best = g->rows;
    ps_new_block(g, now_ms, steer);
}

/* A pedal counts as pressed above on_pct and as released below half of that, so it can't chatter */
static inline bool ps_pedal_down(bool was_down, float pct, float on_pct)
{
    return was_down ? (pct > on_pct * 0.5f) : (pct > on_pct);
}

/* Call when the game screen is not showing */
static inline void ps_hide(ps_game_t *g)
{
    if (g->state == PS_PLAYING)
        g->state = PS_PAUSED;
    g->brake_was_down = true; /* a pedal already held when the screen comes back doesn't count as a press */
}

/* One step of the game. Call every pass of the UI loop while the game screen is showing.
 * steer: 0 = full left .. 1 = full right. brake, throttle: pedal pressed or not. */
static inline void ps_step(ps_game_t *g, uint32_t now_ms, float steer, bool brake, bool throttle)
{
    bool press = brake && !g->brake_was_down;
    g->brake_was_down = brake;

    if (g->state != PS_PLAYING)
    {
        if (press && g->state == PS_PAUSED)
        {
            g->state = PS_PLAYING;
            g->last_fall_ms = now_ms;
            g->drop_armed = false;
            g->changed = true;
        }
        else if (press && (g->state == PS_READY || now_ms - g->over_ms >= PS_RESTART_MS))
        {
            ps_start(g, now_ms, steer);
            g->changed = true;
        }
        return;
    }

    if (press)
    {
        /* turn; if there is no room, try a few columns either side (3 left: a column at the right wall) */
        static const int8_t nudge[6] = {0, -1, 1, -2, 2, -3};
        uint16_t turned = ps_rotate(g->mask);
        for (int i = 0; i < 6; i++)
            if (!ps_blocked(g, turned, g->x + nudge[i], g->y))
            {
                g->mask = turned;
                g->x = (int8_t)(g->x + nudge[i]);
                g->changed = true;
                break;
            }
    }

    if (now_ms - g->last_move_ms >= PS_MOVE_MS)
    {
        int target = ps_target_column(g->mask, steer);
        int step = (target > g->x) - (target < g->x);
        if (step != 0 && !ps_blocked(g, g->mask, g->x + step, g->y))
        {
            g->x = (int8_t)(g->x + step);
            g->changed = true;
        }
        g->last_move_ms = now_ms;
    }

    if (!throttle)
        g->drop_armed = true;
    uint32_t fall_ms = (throttle && g->drop_armed) ? PS_FALL_DROP_MS : ps_fall_ms(g);
    if (now_ms - g->last_fall_ms >= fall_ms)
    {
        if (!ps_blocked(g, g->mask, g->x, g->y + 1))
        {
            g->y++;
            g->last_fall_ms = now_ms;
        }
        else
        {
            ps_land(g, now_ms, steer);
        }
        g->changed = true;
    }
}
