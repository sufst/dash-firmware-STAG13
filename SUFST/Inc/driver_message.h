/* Driver message: text sent to the car that flashes up in a box over the Endurance, Skidpad and Accel
 * screens, then stays solid, then disappears (the msg_popup widgets in the EEZ Studio project).
 *
 * THE CAN FRAME (what the sender, e.g. the wireless link, has to put on the bus)
 *
 *   Dash_Message   ID 0x700 (standard 11-bit), 8 data bytes, on CAN-S or CAN-T (the dash listens on both)
 *
 *   byte 0   high 4 bits: how many parts the message has, 1 to 4.  0 = clear the message now
 *            low 4 bits:  which part this frame is, counting from 0
 *   byte 1   message number: any value, but it must CHANGE for each new message (just add 1)
 *   byte 2-7 six characters of the text (plain ASCII). Part 0 carries characters 1-6, part 1
 *            carries 7-12 and so on. Fill what is left of the last part with 0
 *
 *   A message is up to 24 characters (4 parts x 6). The dash shows it once it has every part with the
 *   same message number; the parts can come in any order, but all within half a second.
 *
 *   Example, "BOX BOX" as message number 5 (two frames):
 *       700#20 05 42 4F 58 20 42 4F        part 0 of 2:  B O X _ B O
 *       700#21 05 58 00 00 00 00 00        part 1 of 2:  X
 *   Clear the screen early:
 *       700#00 00 00 00 00 00 00 00
 *
 *   Sending the same message more than once (worth doing over a radio link) is fine: frames with the
 *   message number that was just shown are ignored for as long as they keep coming, and for 3 seconds
 *   after. To show the same words again, send them with a new message number.
 *   A new message replaces one that is still on screen.
 *
 * 0x700 is not in can-defs yet: it is free on both buses as of can-defs main, Nov 2026, but agree it
 * with whoever looks after can-defs before relying on it. It is only this one #define.
 *
 * HOW LONG IT SHOWS is set in EEZ Studio (Variables panel), in milliseconds:
 *   driver_msg_show_ms   total time on screen (5000)
 *   driver_msg_flash_ms  how long it flashes before going solid (2000)
 *   driver_msg_blink_ms  time in each flash state (160)
 *
 * The logic is header-only so it can be tested on a PC (C:\dashwork\sim\test_driver_message.c);
 * driver_message.cpp is the firmware side. */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Called for every received CAN frame, from the CAN receive task (can.c). Ignores other IDs */
void driver_message_handle_frame(uint32_t id, const uint8_t *data, uint8_t length);

/* Called every pass of the UI loop (freertos.c), before ui_tick() */
void driver_message_tick(void);

#ifdef __cplusplus
}
#endif

#define DRIVER_MSG_FRAME_ID 0x700U

#define DRIVER_MSG_MAX_PARTS 4U
#define DRIVER_MSG_CHARS_PER_PART 6U
#define DRIVER_MSG_MAX_CHARS (DRIVER_MSG_MAX_PARTS * DRIVER_MSG_CHARS_PER_PART)

/* All parts of a message must arrive within this long of its first part, or it is thrown away */
#define DRIVER_MSG_ASSEMBLY_TIMEOUT_MS 500U

/* A message number that was just shown is ignored until it has been quiet for this long */
#define DRIVER_MSG_REPEAT_WINDOW_MS 3000U

/* ---------------------------------------------------------------- putting the frames together */

typedef struct
{
    char text[DRIVER_MSG_MAX_CHARS + 1];
    bool busy;           /* part-way through a message */
    uint8_t number;      /* its message number */
    uint8_t parts;       /* how many parts it has */
    uint8_t have;        /* one bit per part received */
    uint32_t started_ms; /* when its first part arrived */

    bool any_done;        /* a message has been completed before */
    uint8_t last_number;  /* its number */
    uint32_t last_seen_ms; /* when a frame with that number last arrived */
} driver_msg_rx_t;

typedef enum
{
    DRIVER_MSG_RX_NOTHING, /* nothing to do yet */
    DRIVER_MSG_RX_SHOW,    /* a whole message has arrived: show it */
    DRIVER_MSG_RX_CLEAR    /* take the message off the screen */
} driver_msg_rx_result_t;

/* Feeds one Dash_Message frame in. now_ms is a millisecond clock (wrap-around is fine).
 * On DRIVER_MSG_RX_SHOW, out holds the text: printable ASCII only (anything else becomes '?'),
 * with spaces trimmed off both ends. */
static inline driver_msg_rx_result_t driver_msg_rx_frame(driver_msg_rx_t *rx, const uint8_t *data, uint8_t length,
                                                         uint32_t now_ms, char out[DRIVER_MSG_MAX_CHARS + 1])
{
    if (length < 2U)
    {
        return DRIVER_MSG_RX_NOTHING;
    }
    if (length > 8U)
    {
        length = 8U;
    }

    uint8_t parts = (uint8_t)(data[0] >> 4);
    uint8_t index = (uint8_t)(data[0] & 0x0FU);
    uint8_t number = data[1];

    if (parts == 0U)
    {
        rx->busy = false;
        return DRIVER_MSG_RX_CLEAR;
    }
    if (parts > DRIVER_MSG_MAX_PARTS || index >= parts)
    {
        return DRIVER_MSG_RX_NOTHING;
    }

    /* A repeat of the message just shown */
    if (rx->any_done && number == rx->last_number && (now_ms - rx->last_seen_ms) < DRIVER_MSG_REPEAT_WINDOW_MS)
    {
        rx->last_seen_ms = now_ms;
        return DRIVER_MSG_RX_NOTHING;
    }

    if (!rx->busy || number != rx->number || parts != rx->parts ||
        (now_ms - rx->started_ms) > DRIVER_MSG_ASSEMBLY_TIMEOUT_MS)
    {
        memset(rx->text, 0, sizeof(rx->text));
        rx->busy = true;
        rx->number = number;
        rx->parts = parts;
        rx->have = 0U;
        rx->started_ms = now_ms;
    }

    for (uint8_t i = 0U; i < DRIVER_MSG_CHARS_PER_PART; i++)
    {
        uint8_t c = (uint8_t)((2U + i) < length ? data[2U + i] : 0U);
        if (c != 0U && (c < 32U || c > 126U))
        {
            c = (uint8_t)'?';
        }
        rx->text[index * DRIVER_MSG_CHARS_PER_PART + i] = (char)c;
    }
    rx->have |= (uint8_t)(1U << index);

    if (rx->have != (uint8_t)((1U << parts) - 1U))
    {
        return DRIVER_MSG_RX_NOTHING;
    }

    /* Complete. The text ends at the first 0; trim spaces off both ends */
    rx->busy = false;
    rx->any_done = true;
    rx->last_number = number;
    rx->last_seen_ms = now_ms;

    const char *start = rx->text;
    while (*start == ' ')
    {
        start++;
    }
    size_t len = strlen(start);
    while (len > 0U && start[len - 1U] == ' ')
    {
        len--;
    }
    memcpy(out, start, len);
    out[len] = '\0';

    return len > 0U ? DRIVER_MSG_RX_SHOW : DRIVER_MSG_RX_CLEAR;
}

/* ---------------------------------------------------------------- what the pop-up looks like over time */

typedef struct
{
    bool visible; /* the pop-up is on screen */
    bool flash;   /* ...and in the outline half of a flash (false = the filled box) */
} driver_msg_view_t;

/* age_ms: time since the message arrived. It flashes (filled, outline, filled, ...) for flash_ms, changing
 * every blink_ms, then stays filled until show_ms. blink_ms or flash_ms of 0 means no flashing. */
static inline driver_msg_view_t driver_msg_view(uint32_t age_ms, int32_t show_ms, int32_t flash_ms, int32_t blink_ms)
{
    driver_msg_view_t view = {false, false};
    if (show_ms <= 0 || age_ms >= (uint32_t)show_ms)
    {
        return view;
    }
    view.visible = true;
    if (blink_ms > 0 && flash_ms > 0 && age_ms < (uint32_t)flash_ms)
    {
        view.flash = ((age_ms / (uint32_t)blink_ms) % 2U) == 1U;
    }
    return view;
}
