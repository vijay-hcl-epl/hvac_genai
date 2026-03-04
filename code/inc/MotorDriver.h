#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdbool.h>

void MotorDriver_Init(void);
void MotorDriver_SetOutput(bool enable, bool forward);
void MotorDriver_Stop(void);

#endif // MOTOR_DRIVER_H
