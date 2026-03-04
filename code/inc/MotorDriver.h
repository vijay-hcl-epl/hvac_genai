#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdbool.h>
#include "SystemTypes.h"

void MotorDriver_SetDirection(enum MotorDirection dir);
void MotorDriver_Enable(bool en);
void MotorDriver_Stop(void);

#endif // MOTOR_DRIVER_H
