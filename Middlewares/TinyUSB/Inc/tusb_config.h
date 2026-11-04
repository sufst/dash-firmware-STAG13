#ifndef TUSB_CONFIG_H
#define TUSB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

// ── MCU & port ───────────────────────────────────────────────────────────────
// OPT_MCU_STM32F7 is injected via -D in CMakeLists, but also set here as a
// fallback so clangd / IDEs see it.
#ifndef CFG_TUSB_MCU
  #define CFG_TUSB_MCU OPT_MCU_STM32F7
#endif

// Using the OTG_HS peripheral with the *internal* FS PHY.
// rhport 0 = OTG_FS peripheral, rhport 1 = OTG_HS peripheral.
// Internal PHY on OTG_HS tops out at Full Speed (12 Mbps).
#define BOARD_DEVICE_RHPORT_NUM     1
#define BOARD_DEVICE_RHPORT_SPEED   OPT_MODE_FULL_SPEED
#define CFG_TUSB_RHPORT1_MODE       (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)
#define CFG_TUD_MAX_SPEED           OPT_MODE_FULL_SPEED
#define CFG_TUSB_DW2_INTERNAL_PHY   1

// ── OS ───────────────────────────────────────────────────────────────────────
// Bare-metal – call tud_task() from the main loop.
#define CFG_TUSB_OS                 OPT_OS_NONE

// ── Debug ────────────────────────────────────────────────────────────────────
#define CFG_TUSB_DEBUG              2   // Set to 2 for verbose logging

// ── Device classes ───────────────────────────────────────────────────────────
#define CFG_TUD_CDC                 1
#define CFG_TUD_MSC                 1
#define CFG_TUD_HID                 0
#define CFG_TUD_MIDI                0
#define CFG_TUD_VENDOR              0

// ── Buffer sizes ─────────────────────────────────────────────────────────────
#define CFG_TUD_CDC_RX_BUFSIZE      512
#define CFG_TUD_CDC_TX_BUFSIZE      512
#define CFG_TUD_CDC_EP_BUFSIZE      64

#define CFG_TUD_MSC_EP_BUFSIZE      512

#ifdef __cplusplus
}
#endif
#endif /* TUSB_CONFIG_H */