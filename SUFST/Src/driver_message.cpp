/* Driver message, firmware side: takes Dash_Message frames from the CAN receive task, and gives the
 * screens the text and the pop-up's state (driver_msg, driver_msg_visible, driver_msg_flash).
 * The frame format, and where the timings are set, are described in driver_message.h. */

#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "main.h"

#include "driver_message.h"
#include "eez-flow.h"
#include "vars.h"

/* Used by the CAN receive task only */
static driver_msg_rx_t rx;

/* Handed from the CAN receive task to the UI task; only touched inside a critical section */
enum pending_t
{
    PENDING_NONE,
    PENDING_SHOW,
    PENDING_CLEAR
};
static pending_t pending = PENDING_NONE;
static char pending_text[DRIVER_MSG_MAX_CHARS + 1];

/* Used by the UI task only */
static char shown_text[DRIVER_MSG_MAX_CHARS + 1] = "";
static bool active = false;
static uint32_t shown_at_ms = 0;
static driver_msg_view_t view = {false, false};

/* Puts one Dash_Message frame through the given assembler and, when that completes a message (or is a
 * clear), hands the result to the UI task */
static void feed(driver_msg_rx_t *state, const uint8_t *data, uint8_t length)
{
    char text[DRIVER_MSG_MAX_CHARS + 1];
    driver_msg_rx_result_t result = driver_msg_rx_frame(state, data, length, HAL_GetTick(), text);
    if (result == DRIVER_MSG_RX_NOTHING)
    {
        return;
    }

    taskENTER_CRITICAL();
    if (result == DRIVER_MSG_RX_SHOW)
    {
        memcpy(pending_text, text, sizeof(pending_text));
        pending = PENDING_SHOW;
    }
    else
    {
        pending = PENDING_CLEAR;
    }
    taskEXIT_CRITICAL();
}

extern "C" void driver_message_handle_frame(uint32_t id, const uint8_t *data, uint8_t length)
{
    if (id != DRIVER_MSG_FRAME_ID)
    {
        return;
    }
    feed(&rx, data, length);
}

#ifdef DRIVER_MSG_SELFTEST
/* SELF-TEST BUILD ONLY (cmake -DDASH_MSG_SELFTEST=ON): for trying the pop-up on the real dash with nothing
 * sending Dash_Message. The dash makes up the CAN frames for a test message itself, the first 5 s after
 * power-up and then one every 20 s, and puts them through the same decoder a received frame goes through.
 * Messages that really arrive on CAN still work. Never race with this build. */
#define SELFTEST_FIRST_MS 5000U
#define SELFTEST_EVERY_MS 20000U

static void selftest_tick(uint32_t now)
{
    static const char *const texts[] = {"SKILL ISSUE", "BOX BOX", "PIT THIS LAP FOR TYRES!!", "PUSH"};
    static driver_msg_rx_t selftest_rx; /* its own assembler, so it can't disturb one from the CAN task */
    static uint32_t next_ms = SELFTEST_FIRST_MS;
    static uint8_t number = 0;

    if ((int32_t)(now - next_ms) < 0)
    {
        return;
    }
    next_ms += SELFTEST_EVERY_MS;

    const char *text = texts[number % (sizeof(texts) / sizeof(texts[0]))];
    size_t len = strlen(text);
    uint8_t parts = (uint8_t)((len + DRIVER_MSG_CHARS_PER_PART - 1U) / DRIVER_MSG_CHARS_PER_PART);
    for (uint8_t i = 0; i < parts; i++)
    {
        uint8_t d[8] = {(uint8_t)((parts << 4) | i), number, 0, 0, 0, 0, 0, 0};
        for (uint8_t k = 0; k < DRIVER_MSG_CHARS_PER_PART && (size_t)(i * DRIVER_MSG_CHARS_PER_PART + k) < len; k++)
        {
            d[2 + k] = (uint8_t)text[i * DRIVER_MSG_CHARS_PER_PART + k];
        }
        feed(&selftest_rx, d, 8);
    }
    number++;
}
#endif

static int32_t setting(enum FlowGlobalVariables index)
{
    return eez::flow::getGlobalVariable(index).toInt32();
}

extern "C" void driver_message_tick(void)
{
    uint32_t now = HAL_GetTick();

#ifdef DRIVER_MSG_SELFTEST
    selftest_tick(now);
#endif

    taskENTER_CRITICAL();
    pending_t todo = pending;
    pending = PENDING_NONE;
    if (todo == PENDING_SHOW)
    {
        memcpy(shown_text, pending_text, sizeof(shown_text));
    }
    taskEXIT_CRITICAL();

    if (todo == PENDING_SHOW)
    {
        active = true;
        shown_at_ms = now;
    }
    else if (todo == PENDING_CLEAR)
    {
        active = false;
    }

    view.visible = false;
    view.flash = false;
    if (active)
    {
        /* EEZ Studio variables, milliseconds. If these don't compile, the variables haven't been added in
         * EEZ Studio yet (C:\dashwork\add_driver_message.py adds them) or the project needs a Build. */
        view = driver_msg_view(now - shown_at_ms, setting(FLOW_GLOBAL_VARIABLE_DRIVER_MSG_SHOW_MS),
                               setting(FLOW_GLOBAL_VARIABLE_DRIVER_MSG_FLASH_MS),
                               setting(FLOW_GLOBAL_VARIABLE_DRIVER_MSG_BLINK_MS));
        active = view.visible;
    }
}

/* The EEZ Studio native variables the msg_popup widgets use */

extern "C" const char *get_var_driver_msg()
{
    return shown_text;
}

extern "C" void set_var_driver_msg(const char *value)
{
    (void)value;
}

extern "C" bool get_var_driver_msg_visible()
{
    return view.visible;
}

extern "C" void set_var_driver_msg_visible(bool value)
{
    (void)value;
}

extern "C" bool get_var_driver_msg_flash()
{
    return view.visible && view.flash;
}

extern "C" void set_var_driver_msg_flash(bool value)
{
    (void)value;
}
