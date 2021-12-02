#include <stdio.h>
#include "main.h"
#include "serial.h"
#include "keyboard.h"

/*
Reference:
    - https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf 
    - Table 12
*/

////////////////////////////////////////////////////////////////////////////////////////
KeyboardContext KeyboardContext_init() {
    // set all columns to high
    for (uint8_t i = 0; i < NUM_COLS; i++) { _set_col(i); }

    KeyboardContext ret = {
        .KEY_MATRIX = {
            {
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
            },
            {
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
            },
            {
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
            },
            {
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
            },
            {
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
                {.state = UNPRESSED, .report_keycode = UNUSED_KEYCODE},
            }
        },
        .KEY_POS_TO_KEYCODE_LUT = {
            {
                0x83,   // row0, col0 ==> numlock
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
        }
    };
    ret.REPORT = HIDReport_init();
    return ret;
}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
uint8_t _row_map[5] = {
    0x05,
    0x04,
    0x03,
    0x02,
    0x01
};
uint8_t _row_is_set(uint8_t r) {
    return ((ROW0_GPIO_Port->IDR >> _row_map[r]) & 1);
}

void _set_col(uint8_t c) {
    COL0_GPIO_Port->ODR |= ((1 << c) << COL_OFFSET);
}
void _clear_col(uint8_t c) {
    COL0_GPIO_Port->ODR &= ~((1 << c) << COL_OFFSET);
}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
void scan_keys(KeyboardContext* ctx) {
    for (uint8_t c = 0; c < NUM_COLS; c++) {
        _clear_col(c);
        for (uint8_t r = 0; r < NUM_ROWS; r++) {
            uint8_t pressed = !_row_is_set(r);

            if ( pressed && (ctx->KEY_MATRIX[r][c].state == UNPRESSED) ) {
                ctx->KEY_MATRIX[r][c].state = RECENT_PRESS;
            }
            else if ( pressed && (ctx->KEY_MATRIX[r][c].state == RECENT_PRESS) ) {
                ctx->KEY_MATRIX[r][c].state = STALE_PRESS;

                uint8_t keycode = HIDReport_get_available_keycode(&ctx->REPORT);
                ctx->KEY_MATRIX[r][c].report_keycode = keycode;
                HIDReport_set_keycode(&ctx->REPORT, keycode, ctx->KEY_POS_TO_KEYCODE_LUT[r][c]);
            }
            else if (!pressed) {
                ctx->KEY_MATRIX[r][c].state = UNPRESSED;

                uint8_t keycode = ctx->KEY_MATRIX[r][c].report_keycode;

                if (keycode != UNUSED_KEYCODE) {
                    ctx->KEY_MATRIX[r][c].report_keycode = UNUSED_KEYCODE;
                    HIDReport_free_keycode(&ctx->REPORT, keycode);
                }

                HIDReport_set_keycode(&ctx->REPORT, keycode, HID_RELEASE_KEY);
            }
        }
        _set_col(c);
    }
}

void send_keys(KeyboardContext* ctx) {
    HIDReport_send(&ctx->REPORT);
}
////////////////////////////////////////////////////////////////////////////////////////
