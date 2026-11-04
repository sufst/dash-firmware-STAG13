#include "tusb.h"
#include "diskio.h"
#include "usb_mode.h"

#define SD_DISK_NUM  0

// ── Inquiry ────────────────────────────────────────────────────────────────
void tud_msc_inquiry_cb(uint8_t lun, uint8_t vendor_id[8],
                        uint8_t product_id[16], uint8_t product_rev[4])
{
    (void)lun;
    memcpy(vendor_id,   "SUFST   ", 8);
    memcpy(product_id,  "SD Card         ", 16);
    memcpy(product_rev, "1.0 ", 4);
}

// ── Ready check ────────────────────────────────────────────────────────────
// If not in MSC mode the host never sees the card at all
bool tud_msc_test_unit_ready_cb(uint8_t lun)
{
    (void)lun;

    if (!msc_mode)
        return false;

    return (disk_status(SD_DISK_NUM) == 0);
}

// ── Capacity ───────────────────────────────────────────────────────────────
void tud_msc_capacity_cb(uint8_t lun, uint32_t *block_count,
                         uint16_t *block_size)
{
    (void)lun;

    if (!msc_mode)
    {
        *block_count = 0;
        *block_size  = 512;
        return;
    }

    disk_ioctl(SD_DISK_NUM, GET_SECTOR_COUNT, block_count);
    disk_ioctl(SD_DISK_NUM, GET_SECTOR_SIZE,  block_size);
}

// ── Read ───────────────────────────────────────────────────────────────────
int32_t tud_msc_read10_cb(uint8_t lun, uint32_t lba, uint32_t offset,
                           void *buffer, uint32_t bufsize)
{
    (void)lun;
    (void)offset;

    if (!msc_mode)
        return -1;

    uint32_t sectors = bufsize / 512;
    if (disk_read(SD_DISK_NUM, buffer, lba, sectors) != RES_OK)
        return -1;

    return (int32_t)bufsize;
}

// ── Write ──────────────────────────────────────────────────────────────────
int32_t tud_msc_write10_cb(uint8_t lun, uint32_t lba, uint32_t offset,
                            uint8_t *buffer, uint32_t bufsize)
{
    (void)lun;
    (void)offset;

    if (!msc_mode)
        return -1;

    uint32_t sectors = bufsize / 512;
    if (disk_write(SD_DISK_NUM, buffer, lba, sectors) != RES_OK)
        return -1;

    return (int32_t)bufsize;
}

// ── SCSI passthrough ───────────────────────────────────────────────────────
int32_t tud_msc_scsi_cb(uint8_t lun, uint8_t const scsi_cmd[16],
                         void *buffer, uint16_t bufsize)
{
    (void)lun; (void)scsi_cmd; (void)buffer; (void)bufsize;
    return -1;
}

// ── Write protect ──────────────────────────────────────────────────────────
bool tud_msc_is_writable_cb(uint8_t lun)
{
    (void)lun;
    return true;
}