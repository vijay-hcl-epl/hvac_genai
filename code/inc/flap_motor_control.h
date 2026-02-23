#ifndef FLAP_MOTOR_CONTROL_H
#define FLAP_MOTOR_CONTROL_H
#include <stdint.h>
void FlapMotorControl_Init(void);
void FlapMotorControl_MoveTo(uint8_t target);
void FlapMotorControl_Stop(void);
void FlapMotorControl_Update(void);
#endif // FLAP_MOTOR_CONTROL_H
