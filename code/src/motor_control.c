#include "motor_control.h"
#include <stdint.h>

static motor_state_t motor_state = MOTOR_STATE_DISABLED;
static int motor_fault = 0;

// Stub for GPIO/driver config.
static void set_motor_pins(motor_state_t state) {
    // Hardware-specific function to set outputs
    // Replace this with actual GPIO/H-bridge code
}

void motor_control_move(motor_dir_t dir) {
    if (motor_fault) {
        set_motor_pins(MOTOR_STATE_DISABLED);
        motor_state = MOTOR_STATE_DISABLED;
        return;
    }
    if (dir == MOTOR_DIR_FWD) {
        set_motor_pins(MOTOR_STATE_FWD);
        motor_state = MOTOR_STATE_FWD;
    } else {
        set_motor_pins(MOTOR_STATE_REV);
        motor_state = MOTOR_STATE_REV;
    }
}

void motor_control_stop(void) {
    set_motor_pins(MOTOR_STATE_DISABLED);
    motor_state = MOTOR_STATE_DISABLED;
}

int motor_control_status(void) {
    return (int)motor_state;
}

void motor_control_fault(void) {
    motor_fault = 1;
    set_motor_pins(MOTOR_STATE_DISABLED);
    motor_state = MOTOR_STATE_DISABLED;
}
