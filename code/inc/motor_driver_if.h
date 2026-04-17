#ifndef MOTOR_DRIVER_IF_H
#define MOTOR_DRIVER_IF_H
#include <stdint.h>
void motor_driver_if_init(void);
// Drives motor to move towards target; directions based on (target - actual)
void motor_driver_if_drive(uint8_t target, uint8_t actual);
// Immediately stops all drive PWM/GPIO
void motor_driver_if_stop(void);
#endif
