# Dashboard Firmware (Stag 13)

Dashboard firmware for a STM32F746ZGT connected to two CAN buses (CAN-T and CAN-S, with definitions [here](https://github.com/sufst/can-defs)), using EEZ Studio + LVGL for rendering. 

## Updating the UI
Open `eez-Stag13/Stag13.eez-project` in EEZ Studio

## Adding signals
1. Open `Codegen/signal_mapping.yaml`
2. Add the CAN frames and signals you want to be accessible inside EEZ studio
3. Make sure EEZ studio is *closed*, then:
4. Run the generation: `cd Codegen && uv sync && uv run main.py` ([uv installation guide](https://docs.astral.sh/uv/#installation))
5. Open the project inside EEZ studio, hit check then build, save the project
6. Check the project builds properly (see below)

## To build and flash
- To build: `make`
- To flash with the st-link connected: `make flash`
