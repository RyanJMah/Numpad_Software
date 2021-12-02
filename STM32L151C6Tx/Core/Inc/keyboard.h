#pragma once

#include "main.h"

#define SCANNING_PERIOD     8

#define NUM_ROWS            5
#define NUM_COLS            4
#define NUM_KEYS            17

#define COL_OFFSET          12

///////////////////////////////////////////////////////////////
typedef enum {
    UNPRESSED = 0,
    RECENT_PRESS = 1,
    STALE_PRESS = 2
} KeyState;

typedef struct {
    KeyState KEY_MATRIX[NUM_ROWS][NUM_COLS];
    const uint8_t KEYMAP[NUM_ROWS][NUM_COLS];
} KeyboardContext;

KeyboardContext KeyboardContext_init();
uint8_t _row_is_set(uint8_t r);
void _set_col(uint8_t c);
void _clear_col(uint8_t c);
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
#define HID_RELEASE_KEY     0x00
#define HID_NUM_KEYS        6
#define HID_REPORT_SIZE     8

typedef struct {
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keycode1;
    uint8_t keycode2;
    uint8_t keycode3;
    uint8_t keycode4;
    uint8_t keycode5;
    uint8_t keycode6;
} _HIDReport;

typedef union {
    _HIDReport fields;
    uint8_t bytes[6];
} HIDReport;

///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
void scan_keys(KeyboardContext* ctx);
void send_keys(KeyboardContext* ctx);
///////////////////////////////////////////////////////////////
