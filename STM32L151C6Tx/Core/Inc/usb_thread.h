#pragma once

#include "cmsis_os.h"

extern osThreadId_t usb_thread;
extern const osThreadAttr_t usb_thread_attrs;
void usb_thread_fn(void* arg);

