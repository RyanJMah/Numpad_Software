#include "keyboard.h"
#include "serial.h"

/*
Reference:
    - https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf 
    - Table 12
*/

KeyState KEY_MATRIX[NUM_ROWS][NUM_COLS] = { {UNPRESSED} };

uint8_t KEYMAP[NUM_ROWS][NUM_COLS] = {
    {
        0x53,   // row0, col0 ==> numlock
        0x54,   // row0, col1 ==> /
        0x55,   // row0, col2 ==> *
        0x56    // row0, col3 ==> -
    },
    {
        0x5F,   // row1, col0 ==> 7
        0x60,   // row1, col1 ==> 8
        0x61,   // row1, col2 ==> 9
        0x57    // row1, col3 ==> +
    },
    {
        0x5C,   // row2, col0 ==> 4
        0x5D,   // row2, col1 ==> 5
        0x5E,   // row2, col2 ==> 6
        0x58    // row2, col3 ==> enter
    },
    {
        0x59,   // row3, col0 ==> 1
        0x5A,   // row3, col1 ==> 2
        0x5B,   // row3, col2 ==> 3
        0x62    // row3, col3 ==> 0
    },
    {
        0x63,   // row4, col0 ==> . 
        0xff,   // invalid
        0xff,   // invalid
        0xff    // invalid
    }
};

uint8_t _row_map[5] = {
    0x05,
    0x04,
    0x03,
    0x02,
    0x01
};
uint8_t row_is_set(uint8_t r) {
    return ((ROW0_GPIO_Port->IDR >> _row_map[r]) & 1);
}

void set_col(uint8_t c) {
    COL0_GPIO_Port->ODR |= ((1 << c) << COL_OFFSET);
}
void clear_col(uint8_t c) {
    COL0_GPIO_Port->ODR &= ~((1 << c) << COL_OFFSET);
}
