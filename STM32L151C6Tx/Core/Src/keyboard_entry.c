#include <stdio.h>
#include "main.h"
#include "serial.h"
#include "keyboard.h"
#include "usb_thread.h"
#include "keyscan_thread.h"
#include "keyboard_entry.h"

osThreadId_t keyscan_thread;
osThreadId_t usb_thread;

int keyboard_entry() {
    serial_init();

    printf("initializing USB...\r\n");
    // MX_USB_DEVICE_Init();

    serial_init();

    printf("initializing kernel...\r\n");
    osKernelInitialize();

    printf("initializing threads...\r\n");

    KeyboardContext arg = KeyboardContext_init();
    keyscan_thread = osThreadNew(keyscan_thread_fn, (void*)(&arg), &keyscan_thread_attrs);
    usb_thread = osThreadNew(usb_thread_fn, (void*)(&arg), &usb_thread_attrs);

    printf("starting kerenel...\r\n");
    osKernelStart();

    // should never reach this point, we have handed execution over to the RTOS
    Error_Handler();

    return 0;
}
