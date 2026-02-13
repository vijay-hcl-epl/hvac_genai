#ifndef MAIN_COORDINATOR_H
#define MAIN_COORDINATOR_H

#include <stdint.h>
#include "uart_cmd_handler.h"
#include "motor_control.h"
#include "feedback_processor.h"
#include "led_control.h"

typedef enum {
    SYS_INIT,
    SYS_IDLE,
    SYS_MOVING,
    SYS_HOLD
} system_mode_t;

typedef struct {
    system_mode_t mode;
    int8_t target_position;
    int8_t last_position;
    uint8_t error_flag;
} coordinator_state_t;

void coordinator_init(void);
void coordinator_main_loop(void);

#endif // MAIN_COORDINATOR_H
/* MISRA: Rule 20.3 – Ending preprocessor directives with comments for readability */
