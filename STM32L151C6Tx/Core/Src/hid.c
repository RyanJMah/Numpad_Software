#include "main.h"
#include "usbd_hid.h"
#include "hid.h"

HIDReport HIDReport_init() {
    HIDReport ret = {
        .report = { {0x00} },
        .keycode_usage = {UNUSED_KEYCODE}
    };
    return ret;
}

void HIDReport_set_keycode(HIDReport* this, uint8_t keycode, uint8_t val) {
    if (keycode != UNUSED_KEYCODE) {
        this->report.bytes[keycode + 1] = val;
    }
}

uint8_t HIDReport_get_available_keycode(HIDReport* this) {
    uint8_t ret = UNUSED_KEYCODE;
    for (uint8_t i = 0; i < HID_NUM_KEYS; i++) {
        if (this->keycode_usage[i] == UNUSED_KEYCODE) {
            ret = i + 1;
            break;
        }
    }
    return ret;
}
void HIDReport_free_keycode(HIDReport* this, uint8_t keycode) {
    this->keycode_usage[keycode] = UNUSED_KEYCODE;
}

void HIDReport_send(HIDReport* this) {
    USBD_HID_SendReport(&hUsbDeviceFS, this->report.bytes, HID_REPORT_SIZE);
}
