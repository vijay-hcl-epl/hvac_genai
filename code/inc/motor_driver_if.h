#ifndef MOTOR_DRIVER_IF_H
#define MOTOR_DRIVER_IF_H
#include <stdint.h>

void MotorDriverIF_Init(void);
void MotorDriverIF_Drive(uint8_t direction, uint8_t duty);
void MotorDriverIF_Brake(void);
void MotorDriverIF_Off(void);

#endif // MOTOR_DRIVER_IF_H
