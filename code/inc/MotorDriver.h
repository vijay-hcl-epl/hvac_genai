#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include <stdint.h>
void MotorDriver_Init(void);
void MotorDriver_SetMotor(int8_t dir); /* MISRA: Rule 8.2 – Use explicit argument types, avoid implicit int */
#endif /* MISRA: Rule 20.5 – Preprocessor #endif should have comment */
