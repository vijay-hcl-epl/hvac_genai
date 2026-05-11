#include "motor_actuator.h"

static enum {MOTOR_OFF, MOTOR_ON} motor_state;

void motor_actuator_init(void)
{
    motor_state = MOTOR_OFF;
    // HW: set outputs to OFF
}

void motor_actuator_move(void)
{
    motor_state = MOTOR_ON;
    // HW: enable output
}

void motor_actuator_stop(void)
{
    motor_state = MOTOR_OFF;
    // HW: disable output
}
