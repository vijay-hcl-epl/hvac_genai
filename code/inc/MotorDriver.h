#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include <stdint.h>
void MotorDriver_Init(void);
void MotorDriver_SetMotor(int8_t dir); // -1=reverse, 0=stop, 1=forward
#endif // MOTORDRIVER_H
