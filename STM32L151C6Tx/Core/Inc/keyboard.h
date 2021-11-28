#pragma once

#include "main.h"

#define SCANNING_PERIOD     8

#define NUM_ROWS            5
#define NUM_COLS            4
#define NUM_KEYS            17

#define COL_OFFSET          12

typedef enum {
    UNPRESSED = 0,
    RECENT_PRESS = 1,
    STALE_PRESS = 2
} KeyState;

extern KeyState KEY_MATRIX[NUM_ROWS][NUM_COLS];

extern uint8_t KEYMAP[NUM_ROWS][NUM_COLS];

uint8_t row_is_set(uint8_t r);
void set_col(uint8_t c);
void clear_col(uint8_t c);
