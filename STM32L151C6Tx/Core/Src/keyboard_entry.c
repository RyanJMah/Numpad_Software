#include <stdio.h>
#include "main.h"
#include "serial.h"
#include "keyboard.h"

#include "usbd_hid.h"

KeyboardContext ctx;

int keyboard_entry() {
    serial_init();

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
