#pragma once

#include "main.h"
#include "hid.h"

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
    KeyState state;
    uint8_t report_keycode;
} KeyContext;

typedef struct {
    HIDReport REPORT;

    KeyContext KEY_MATRIX[NUM_ROWS][NUM_COLS];
    
    uint8_t KEY_POS_TO_KEYCODE_LUT[NUM_ROWS][NUM_COLS];
} KeyboardContext;

KeyboardContext KeyboardContext_init();
uint8_t _row_is_set(uint8_t r);
void _set_col(uint8_t c);
void _clear_col(uint8_t c);
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
void scan_keys(KeyboardContext* ctx);
void send_keys(KeyboardContext* ctx);
///////////////////////////////////////////////////////////////
