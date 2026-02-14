#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdint.h>
void MotorDriver_Init(void);
int Motor_Drive_Set(uint8_t direction, uint8_t pwm);
void Motor_Drive_Stop(void);
#endif // MOTOR_DRIVER_H
