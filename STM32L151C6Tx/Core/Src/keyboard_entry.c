#include <stdio.h>
#include "main.h"
#include "serial.h"
#include "keyboard.h"

#include "usbd_hid.h"

KeyboardContext ctx;

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
//     // printf("timer done...\r\n");
//     // send_keys(&ctx);
//     HIDReport hid = {0x00};
//     hid.fields.modifier = 0x00;
//     hid.fields.keycode1 = 0x05;
//     USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)(&hid), sizeof(HIDReport));
// }

int keyboard_entry() {
    serial_init();

    // printf("starting timer 3 with interrupt...\r\n");
    // HAL_TIM_Base_Start_IT(&htim3);

    printf("initializing keyboard context...\r\n");
    ctx = KeyboardContext_init();

    printf("entering mainloop...\r\n");
    while (1) {
        scan_keys(&ctx);
        send_keys(&ctx);
        HAL_Delay(8);
    }

    return 0;
}
