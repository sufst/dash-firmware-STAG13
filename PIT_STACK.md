# Pit Stack: the game on the dash

A block-stacking game for when the car is parked with the tractive system off. Blocks of 2 to 4 squares fall into a well 12 squares wide and 16 high. A full row disappears and scores 1. It gets faster every 8 rows and ends when a new block has no room.

It costs about 5 KB of flash and 350 bytes of RAM. It uses no pictures and no new fonts.

## Playing

The dash has no buttons, so the game is played with the car's own controls, read from the VCU (`VCU_Sensors` on CAN-S):

| Control | Does |
|---|---|
| Steering wheel | Where the block is: wheel left = block at the left wall, wheel right = right wall |
| Brake pedal | Turns the block, once per press. Also starts, resumes and restarts the game |
| Throttle pedal | Drops the block fast while held. Lift it between blocks |

Turn the drive-mode dial to **position 8** with the car switched on at low voltage only.

## When it is allowed on screen

Only on dial position 8, and only while **all** of these are true:

- the VCU is sending, and its state is `TS Button Wait` (tractive system off, nobody has asked for it)
- no tractive system voltage is detected
- wheel speeds are arriving and all four wheels are stopped

If any one stops being true the dash leaves the game on the next pass of its loop (5 ms) and shows the Debug screen, which is what position 8 showed before. A game in progress is paused and kept; press the brake to carry on once the game is back. With the dash alone on the bench (no VCU) position 8 shows Debug.

The rule is `pit_stack_allowed()` in `SUFST/Src/pit_stack.cpp`.

## Setting it up for the car

In EEZ Studio's Variables panel:

| Variable | Default | Meaning |
|---|---|---|
| `game_steer_left` | 30 | Steering reading (`VCU_SAGL`, %) at which the block is at the left wall |
| `game_steer_right` | 70 | The same for the right wall. If the block goes the wrong way, swap the two numbers |
| `game_pedal_pct` | 20 | How far a pedal must be pressed to count, % |

The steering numbers are guesses: read the steering value on the Debug screen with the wheel a comfortable amount left and right, and put those in.

## Changing the look

The `Game` screen in EEZ Studio (last in the list) is the frame; the firmware draws only the squares.

| Widget | What |
|---|---|
| `game_well` | The box the blocks fall in. Move or resize it and the squares are drawn as big as fit inside it |
| `game_msg` | The text over the well (`BRAKE TO START`, `GAME OVER`...). Hidden while playing |
| `game_rows_value`, `game_best_value` | Rows this game, and the best since power-up |
| `game_title`, `game_rows_label`, `game_best_label`, `game_help` | Plain text |

The blocks use the theme colours Ok, Warn, Crit and Text. Speeds and the well size are the `PS_...` numbers at the top of `SUFST/Inc/pit_stack.h`.

## Where the code is

| File | What |
|---|---|
| `SUFST/Inc/pit_stack.h` | The whole game, no hardware in it (PC test: `C:\dashwork\sim\test_pit_stack.c`) |
| `SUFST/Src/pit_stack.cpp` | When it is allowed, reading the wheel and pedals, drawing, the screen's variables |
| `SUFST/Inc/pit_stack_fw.h` | The two calls the rest of the firmware uses |
| `SUFST/Src/screen_select.c` | Dial position 8: Game if allowed, otherwise Debug |
| `Core/Src/freertos.c` | Calls `pit_stack_tick()` in the UI loop |

## Not yet checked on the car

- Whether the VCU sends steering and pedal values with the tractive system off (the game needs them).
- The real steering range, and which way it counts.
- Whether the wheel speed readings sit at exactly zero when parked (below 1.0 counts as stopped).
