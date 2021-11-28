#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "main.h"
#include "serial.h"

// redirect STDIN, STDERR, and STDOUT to UART3
void __io_putchar(uint8_t ch) {
    HAL_UART_Transmit(&huart3, &ch, 1, HAL_MAX_DELAY);
}
uint8_t __io_getchar() {
    uint8_t ch;
    HAL_UART_Receive(&huart3, &ch, 1, HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart3, &ch, 1, HAL_MAX_DELAY);
    return ch;
}

void serial_init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void input(char* msg, char* input_buff) {
    printf(msg);
    scanf("%s", input_buff);
    printf("\r\n");
}


