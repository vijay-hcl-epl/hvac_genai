#ifndef MOTOR_DRIVER_IF_H
#define MOTOR_DRIVER_IF_H
#include <stdint.h>
typedef enum { DIR_INC, DIR_DEC } MotorDirection;
void MotorDriver_Init(void);
void MotorDriver_Drive(MotorDirection dir, uint8_t duty);
void MotorDriver_Brake(void);
void MotorDriver_Off(void);
#endif
