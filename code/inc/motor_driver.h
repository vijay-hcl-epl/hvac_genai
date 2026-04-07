#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdint.h>
void MotorDriver_start(int8_t direction);
void MotorDriver_stop(void);
void motor_driver_init(void);
#endif // MOTOR_DRIVER_H
