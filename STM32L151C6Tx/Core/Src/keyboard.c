#include <stdio.h>
#include "main.h"
#include "usbd_hid.h"
#include "serial.h"
#include "keyboard.h"

/*
Reference:
    - https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf 
    - Table 12
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
KeyboardContext KeyboardContext_init() {
    // set all columns to high
    for (uint8_t i = 0; i < NUM_COLS; i++) { _set_col(i); }

    KeyboardContext ret = {
        .KEY_MATRIX = { {UNPRESSED} },
        .KEYMAP = {
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
        }
    };
    return ret;
}

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void scan_keys(KeyboardContext* ctx) {
    for (uint8_t c = 0; c < NUM_COLS; c++) {
        _clear_col(c);
        for (uint8_t r = 0; r < NUM_ROWS; r++) {
            uint8_t pressed = !_row_is_set(r);

            if ( pressed && (ctx->KEY_MATRIX[r][c] == UNPRESSED) ) {
                ctx->KEY_MATRIX[r][c] = RECENT_PRESS;
            }
            else if ( pressed && (ctx->KEY_MATRIX[r][c] == RECENT_PRESS) ) {
                ctx->KEY_MATRIX[r][c] = STALE_PRESS;
            }
            else if (!pressed) {
                ctx->KEY_MATRIX[r][c] = UNPRESSED;
            }
        }
        _set_col(c);
    }
}

void send_keys(KeyboardContext* ctx) {
    // KeyboardHID hid = {0x00};
    // hid.modifier = 0x00;

    // for (uint8_t i = 0; i < 150; i++) {
    //     hid.keycode1 = 0x05;
    //     printf("sent report for 'b'\r\n");
    //     USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)(&hid), sizeof(KeyboardHID));
    // }
    // printf("DONE!!!!!!\r\n");
    // while (1) {
    //     HIDReport tmp = {0x00};
    //     tmp.fields.keycode1 = 0x05;
    //     USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)(&tmp), sizeof(HIDReport));
    //     HAL_Delay(10);

    //     hid.keycode1 = 0x00;
    //     USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)(&hid), sizeof(KeyboardHID));
    //     HAL_Delay(500);
    // }

    HIDReport report = {0x00};
    report.fields.modifier = 0x00;
    report.fields.reserved = 0x00;
    report.fields.keycode1 = 0x00;
    report.fields.keycode2 = 0x00;
    report.fields.keycode3 = 0x00;
    report.fields.keycode4 = 0x00;
    report.fields.keycode5 = 0x00;
    report.fields.keycode6 = 0x00;    

    uint8_t indx = 0;
    for (uint8_t r = 0; r < NUM_ROWS; r++) {
        for (uint8_t c = 0; c < NUM_COLS; c++) {
            if (indx >= HID_REPORT_SIZE) { break; }

            if ( (ctx->KEY_MATRIX[r][c] == STALE_PRESS) || (ctx->KEY_MATRIX[r][c] == RECENT_PRESS) ) {
                printf("%x\r\n", ctx->KEYMAP[r][c]);
                report.bytes[indx] = 0x05;
                indx += 1;
            }
        }
    }
    printf("indx = %d\r\n", indx);
    for (uint8_t i = 0; i < HID_REPORT_SIZE; i++) {
        printf("%d\r\n", report.bytes[i]);
    }
    printf("\r\n");
    USBD_HID_SendReport(&hUsbDeviceFS, report.bytes, HID_REPORT_SIZE);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
