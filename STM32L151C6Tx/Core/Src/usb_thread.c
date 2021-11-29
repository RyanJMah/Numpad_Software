#include <stdio.h>
#include "cmsis_os.h"
#include "usbd_hid.h"
#include "keyboard.h"
#include "usb_thread.h"

const osThreadAttr_t usb_thread_attrs = {
    .name = "usb_thread",
    .stack_size = 1024,
    .priority = (osPriority_t)osPriorityBelowNormal
};

typedef struct {
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keycode1;
    uint8_t keycode2;
    uint8_t keycode3;
    uint8_t keycode4;
    uint8_t keycode5;
    uint8_t keycode6;
} KeyboardHID;

void _send_keys(KeyboardContext* ctx) {
    // KeyboardHID tmp = {0};
    // tmp.modifier = 0x00;
    // tmp.modifier = 0x04;
    // tmp.modifier = 0x05;
    // USBD_HID_SendReport(&hUsbDeviceFS, &tmp, sizeof(KeyboardHID));
    // for (uint8_t r = 0; r < NUM_ROWS; r++) {
    //     for (uint8_t c = 0; c < NUM_COLS; c++) {
    //         if (KEY_MATRIX[r][c] == RECENT_PRESS) {
    //             printf("%x\r\n", KEYMAP[r][c]);
    //         }
    //     }
    // }
}
void usb_thread_fn(void* arg) {
    KeyboardContext* ctx = (KeyboardContext*)arg;

    while (1) {
       _send_keys(ctx);
       osDelay(SCANNING_PERIOD);
    }
}

