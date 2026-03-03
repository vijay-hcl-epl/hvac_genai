#include "motor_control_driver.h"
// Hardware-specific includes needed for GPIO/PWM

static motor_direction_t current_motor_state = MOTOR_DIRECTION_OFF;

void motor_control_driver_init(void) {
    current_motor_state = MOTOR_DIRECTION_OFF;
    // Add HW init here
}

void motor_control_driver_set_direction(motor_direction_t direction) {
    if (direction == current_motor_state)
        return;
    current_motor_state = direction;
    switch (direction) {
        case MOTOR_DIRECTION_FORWARD:
            // Drive motor forward (GPIO/PWM set here)
            break;
        case MOTOR_DIRECTION_REVERSE:
            // Drive motor reverse (GPIO/PWM set here)
            break;
        default:
            motor_control_driver_disable();
            break;
    }
}

void motor_control_driver_disable(void) {
    // Set all motor signals to disable
    current_motor_state = MOTOR_DIRECTION_OFF;
}
