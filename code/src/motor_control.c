#include "motor_control.h"

static MotorDirection last_dir = MOTOR_DIRECTION_STOP;
static bool engaged = false;

void set_motor_direction(MotorDirection dir) {
    // Simulated: Actual GPIO control here based on direction
    last_dir = dir;
    if (dir == MOTOR_DIRECTION_STOP) {
        engaged = false;
    } else {
        engaged = true;
    }
}

bool is_motor_engaged(void) {
    return engaged;
}
