#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdbool.h>

void MotorControl_Init(void);
void MotorControl_MoveTo(int current, int target);
void MotorControl_Stop(void);

#endif // MOTOR_CONTROL_H
