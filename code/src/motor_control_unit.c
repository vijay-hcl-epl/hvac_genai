#include "motor_control_unit.h"
#include <stdio.h>
static motor_state_t state = MOTOR_STOPPED;
static motor_dir_t last_dir = MOTOR_DIR_OFF;

void motor_control_init(void) {
    state = MOTOR_STOPPED;
    last_dir = MOTOR_DIR_OFF;
}

void move_motor_to(int target_pos, motor_dir_t dir) {
    /* MISRA: Violation not auto-fixed – manual review required */
    last_dir = dir;
    state = MOTOR_MOVING;
}

void stop_motor(void) {
    last_dir = MOTOR_DIR_OFF;
    state = MOTOR_STOPPED;
}

motor_state_t get_motor_status(void) {
    return state;
}
