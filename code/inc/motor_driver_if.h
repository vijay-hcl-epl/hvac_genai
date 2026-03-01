// RAG_SOURCE: infineon-tle9851qxw-datasheet-en.pdf §26-27, infineon-tle985xqx-usermanual-en.pdf §27
#ifndef MOTOR_DRIVER_IF_H
#define MOTOR_DRIVER_IF_H
#include <stdint.h>
void MotorDriverIF_Run(uint8_t direction, uint8_t speed);
void MotorDriverIF_Stop(void);
void MotorDriverIF_Brake(void);
void MotorDriverIF_Init(void);
#endif
