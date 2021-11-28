#pragma once

#include "cmsis_os.h"

extern osThreadId_t keyscan_thread;
extern const osThreadAttr_t keyscan_thread_attrs;
void keyscan_thread_fn(void* arg);

