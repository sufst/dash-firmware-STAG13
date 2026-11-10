# Driver messages on the dash

Send a short piece of text to the car and it flashes up in a red box over the middle of the dash, then stays solid, then disappears. It shows on the **Endurance, Skidpad and Accel** screens (not Dyno, Debug or Sponsors).

The dash only listens. Something else on the car (the wireless link) has to put the CAN frame below on the bus.

## The CAN frame: `Dash_Message`

| | |
|---|---|
| ID | `0x700`, standard 11-bit |
| Length | 8 bytes |
| Bus | CAN-S or CAN-T (the dash listens on both) |

| Byte | Meaning |
|---|---|
| 0, high 4 bits | How many parts the message has: 1 to 4. `0` means "clear the message now" |
| 0, low 4 bits | Which part this frame is, counting from 0 |
| 1 | Message number. Any value, but it must **change for every new message** (add 1 each time; 255 wraps to 0) |
| 2 to 7 | Six characters of text, plain ASCII. Part 0 carries characters 1 to 6, part 1 carries 7 to 12, and so on. Fill the rest of the last part with `0` |

Rules the dash follows:

- A message is at most **24 characters** (4 parts of 6). Anything that isn't a printable ASCII character shows as `?`.
- The message shows once every part with the same message number has arrived. Parts can come in any order, but all within **0.5 s** of the first one, otherwise the half message is thrown away.
- **Repeats are safe.** Frames carrying the message number that was just shown are ignored for as long as they keep coming, and for 3 s after. Over a radio link it is worth sending each message two or three times.
- To show the same words again, send them with a new message number.
- A new message replaces one that is still on screen.

### Examples

`BOX BOX` as message number 5:

```
700#20 05 42 4F 58 20 42 4F     part 0 of 2:  B O X _ B O
700#21 05 58 00 00 00 00 00     part 1 of 2:  X
```

Clear the screen early:

```
700#00 00 00 00 00 00 00 00
```

### Sender code

```c
/* Sends text (up to 24 characters) to the dash. Add 1 to number for every new message. */
void dash_message_send(const char *text, uint8_t number)
{
    size_t len = strlen(text);
    if (len > 24) len = 24;
    uint8_t parts = (uint8_t)((len + 5) / 6);
    if (parts == 0) parts = 1;

    for (uint8_t i = 0; i < parts; i++)
    {
        uint8_t d[8] = {(uint8_t)((parts << 4) | i), number, 0, 0, 0, 0, 0, 0};
        for (uint8_t k = 0; k < 6 && (size_t)(i * 6 + k) < len; k++)
        {
            d[2 + k] = (uint8_t)text[i * 6 + k];
        }
        can_send(0x700, d, 8); /* your CAN transmit function */
    }
}
```

`C:\dashwork\can-replay\make_driver_message.py "BOX BOX" 5` prints the frames for any text, to check a sender against.

## How it looks, and changing it

Timings are variables in the EEZ Studio project (Variables panel), in milliseconds. Change the Default value, Build, reflash:

| Variable | Default | Meaning |
|---|---|---|
| `driver_msg_show_ms` | 5000 | Total time a message stays on screen |
| `driver_msg_flash_ms` | 2000 | How long it flashes before going solid. 0 = no flashing |
| `driver_msg_blink_ms` | 160 | Time in each flash state (160 is about 3 flashes a second) |

The pop-up itself is four widgets at the bottom of the widget list on each of the three screens:

| Widget | What it is | Shown when |
|---|---|---|
| `msg_popup` | The filled red box | `driver_msg_visible` |
| `msg_popup_text` (inside it) | The message, black on the red | |
| `msg_popup_flash` | The outline box, drawn on top | `driver_msg_flash` |
| `msg_popup_flash_text` (inside it) | The message, in red | |

They are marked hidden in the editor so they don't cover the screen while you work: click the eye icon next to `msg_popup` or `msg_popup_flash` in the Widgets Structure panel to see them. Skidpad and Accel have the same widgets with `skidpad_` and `accel_` in front of the names.

To restyle it, change the widgets on **Main**, save, close EEZ Studio and run

```
C:\dashwork\venv\Scripts\python.exe C:\dashwork\add_driver_message.py C:\dashwork\dash-firmware-STAG13\eez-Stag13\Stag13.eez-project
```

which copies Main's pop-up to Skidpad and Accel. Then reopen the project and Build.

## Where the code is

| File | What |
|---|---|
| `SUFST/Inc/driver_message.h` | The frame format and all the logic (putting the parts together, repeats, timing) |
| `SUFST/Src/driver_message.cpp` | Firmware side: takes frames from the CAN receive task, feeds `driver_msg`, `driver_msg_visible`, `driver_msg_flash` to the screens |
| `Core/Src/can.c` | Passes every received frame to `driver_message_handle_frame()` |
| `Core/Src/freertos.c` | Calls `driver_message_tick()` in the UI loop |

## Trying it without a sender (self-test build)

Configure with `-DDASH_MSG_SELFTEST=ON` (it is OFF by default) and the dash shows a test message by itself, 5 s after power-up and then every 20 s. This is for checking the pop-up on the real screen on the bench; never run the car with it.

```
cmake --preset Release -B build/Release-white-selftest -DDASH_THEME=dash-white-bg -DDASH_MSG_SELFTEST=ON
cmake --build build/Release-white-selftest
```

## Testing with a real sender

The dash is listen-only on both buses, so it never acknowledges a frame. A CAN adapter connected to the dash alone will not work reliably: test on a bus with at least one other live node (e.g. the VCU). CAN-S is 1 Mbit/s, CAN-T is 500 kbit/s.

## Still to agree

`0x700` is not in `can-defs` yet. It is unused on both buses as of `can-defs` main (Nov 2026), but it needs agreeing with whoever looks after `can-defs`. In the firmware it is one line: `DRIVER_MSG_FRAME_ID` in `driver_message.h`.
