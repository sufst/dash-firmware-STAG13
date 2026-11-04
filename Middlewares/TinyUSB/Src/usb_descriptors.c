#include "tusb.h"

// ── Device descriptor ────────────────────────────────────────────────────────
tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,

    // Use Interface Association Descriptor (IAD) device class so the OS
    // correctly groups the two CDC interfaces together.
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,

    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = 0xCafe,
    .idProduct          = 0x4001,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};

uint8_t const *tud_descriptor_device_cb(void) {
    return (uint8_t const *)&desc_device;
}

// ── Configuration descriptor ─────────────────────────────────────────────────
// Interface numbers
enum {
    ITF_NUM_CDC = 0,    // CDC control
    ITF_NUM_CDC_DATA,   // CDC data
    ITF_NUM_MSC,        // MSC
    ITF_NUM_TOTAL
};

// Endpoint numbers  (0x8x = IN to host, 0x0x = OUT from host)
#define EPNUM_CDC_NOTIF     0x81
#define EPNUM_CDC_OUT       0x02
#define EPNUM_CDC_IN        0x82
#define EPNUM_MSC_OUT       0x03
#define EPNUM_MSC_IN        0x83

#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN + TUD_MSC_DESC_LEN)

uint8_t const desc_configuration[] = {
    // ── Config header ────────────────────────────────────────────────────────
    TUD_CONFIG_DESCRIPTOR(
        1,              // bConfigurationValue
        ITF_NUM_TOTAL,  // bNumInterfaces
        0,              // iConfiguration string index
        CONFIG_TOTAL_LEN,
        0x00,           // bmAttributes – bus powered, no remote wakeup
        500             // bMaxPower in mA (500 mA)
    ),

    // ── CDC (Virtual COM Port) ───────────────────────────────────────────────
    TUD_CDC_DESCRIPTOR(
        ITF_NUM_CDC,        // Interface number (control)
        4,                  // String index
        EPNUM_CDC_NOTIF,    // Notification EP (IN)
        8,                  // Notification EP max packet size
        EPNUM_CDC_OUT,      // Data OUT EP
        EPNUM_CDC_IN,       // Data IN EP
        64                  // Data EP max packet size
    ),

    // ── MSC (Mass Storage – SD card) ─────────────────────────────────────────
    TUD_MSC_DESCRIPTOR(
        ITF_NUM_MSC,    // Interface number
        5,              // String index
        EPNUM_MSC_OUT,  // Bulk OUT
        EPNUM_MSC_IN,   // Bulk IN
        64              // Max packet size (64 for FS)
    ),
};

uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return desc_configuration;
}

// ── String descriptors ───────────────────────────────────────────────────────
char const *string_desc_arr[] = {
    (const char[]){0x09, 0x04},  // 0: English (0x0409)
    "SUFST",                     // 1: Manufacturer
    "Dashboard",                 // 2: Product
    "SUFST-2026-DASH-001",       // 3: Serial number
    "Dash USB Serial",           // 4: CDC interface
    "Dash SD Card",              // 5: MSC interface
};

static uint16_t _desc_str[32 + 1];

uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void)langid;
    uint8_t chr_count;

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    } else {
        if (index >= sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))
            return NULL;

        const char *str = string_desc_arr[index];
        chr_count = (uint8_t)strlen(str);
        if (chr_count > 31) chr_count = 31;

        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
    }

    _desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));
    return _desc_str;
}