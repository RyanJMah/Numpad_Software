#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "keyboard.h"
#include "keyscan_thread.h"

const osThreadAttr_t keyscan_thread_attrs = {
    .name = "keyscan_thread",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 1024
};

void keyscan_thread_fn(void* arg) {
    // set all columns to high
    for (uint8_t i = 0; i < NUM_COLS; i++) { set_col(i); }

    while (1) {
        for (uint8_t c = 0; c < NUM_COLS; c++) {
            clear_col(c);
            for (uint8_t r = 0; r < NUM_ROWS; r++) {
                uint8_t pressed = !row_is_set(r);

                if ( pressed && (KEY_MATRIX[r][c] == UNPRESSED) ) {
                    KEY_MATRIX[r][c] = RECENT_PRESS;
                }
                else if ( pressed && (KEY_MATRIX[r][c] == RECENT_PRESS) ) {
                    KEY_MATRIX[r][c] = STALE_PRESS;
                }
                else if (!pressed) {
                    KEY_MATRIX[r][c] = UNPRESSED;
                }
            }
            set_col(c);
        }

        osDelay(SCANNING_PERIOD);
    }
}


