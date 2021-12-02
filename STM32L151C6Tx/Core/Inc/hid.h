#pragma once

#include <stdint.h>

#define HID_RELEASE_KEY     0x00
#define HID_NUM_KEYS        6
#define HID_REPORT_SIZE     8

#define UNUSED_KEYCODE      0xff

typedef struct {
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keycode1;
    uint8_t keycode2;
    uint8_t keycode3;
    uint8_t keycode4;
    uint8_t keycode5;
    uint8_t keycode6;
} _HIDReportFormat;

typedef union {
    _HIDReportFormat fields;
    uint8_t bytes[6];
} HIDReportFormat;

typedef struct {
    HIDReportFormat report;
    uint8_t keycode_usage[HID_NUM_KEYS];
} HIDReport;

HIDReport HIDReport_init();

void HIDReport_set_keycode(HIDReport* this, uint8_t keycode, uint8_t val);

uint8_t HIDReport_get_available_keycode(HIDReport* this);
void HIDReport_free_keycode(HIDReport* this, uint8_t keycode);

void HIDReport_send(HIDReport* this);

