#include "motor_control_unit.h"
#include <stdio.h>
// Hardware-specific code would be implemented in the actual product.
static motor_state_t state = MOTOR_STOPPED;
static motor_dir_t last_dir = MOTOR_DIR_OFF;

void motor_control_init(void) {
    state = MOTOR_STOPPED;
    last_dir = MOTOR_DIR_OFF;
}

void move_motor_to(int target_pos, motor_dir_t dir) {
    // Actual control output omitted; stub logic:
    last_dir = dir;
    state = MOTOR_MOVING;
    // Simulate PWM output enable etc...
    // User must implement hardware setting.
}

void stop_motor(void) {
    last_dir = MOTOR_DIR_OFF;
    state = MOTOR_STOPPED;
    // Simulate PWM output disable
}

motor_state_t get_motor_status(void) {
    return state;
}
