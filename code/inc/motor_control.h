#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>

typedef enum {
    MOTOR_STOPPED,
    MOTOR_RUNNING
} motor_state_t;

typedef enum {
    MOTOR_OK = 0,
    MOTOR_ALREADY_AT_POSITION,
    MOTOR_INVALID_TARGET
} motor_status_t;

void motor_control_init(void);
motor_status_t motor_move_to(int8_t target_position);
void motor_stop(void);

#endif // MOTOR_CONTROL_H
/* MISRA: Rule 20.3 – Ending preprocessor directives with comments for readability */
