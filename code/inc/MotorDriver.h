#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdint.h>
void MotorDriver_Init(void);
void MotorDriver_SetMove(int8_t direction);
void MotorDriver_Stop(void);
#endif
