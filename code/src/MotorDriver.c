#include "MotorDriver.h"
#include <stddef.h>

static enum MotorDirection direction = MOTOR_DIR_STOP;
static bool enabled = false;

void MotorDriver_SetDirection(enum MotorDirection dir) {
    if(dir == MOTOR_DIR_STOP || dir > MOTOR_DIR_REVERSE) return;
    direction = dir;
    // Here: Set GPIO pins to control actual motor direction
}

void MotorDriver_Enable(bool en) {
    enabled = en;
    // Here: Enable/disable the motor driver GPIO (according to 'enabled')
}

void MotorDriver_Stop(void) {
    enabled = false;
    direction = MOTOR_DIR_STOP;
    // Here: Deactivate all motor output GPIOs
}
