#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>
#include <stdbool.h>

void MotorCtrl_Set(uint8_t direction, bool enable);
void MotorCtrl_Stop(void);

#endif // MOTOR_CONTROL_H
