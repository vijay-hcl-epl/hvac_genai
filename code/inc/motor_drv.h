#ifndef MOTOR_DRV_H
#define MOTOR_DRV_H

#include <stdint.h>
#include <stdbool.h>

void MotorDrv_Init(void);
void MotorDrv_Enable(bool enable);
void MotorDrv_SetDirection(bool dir);
void MotorDrv_SetSpeed(uint8_t duty);
void MotorDrv_Stop(void);

#endif /* MOTOR_DRV_H */
