#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_FORWARD = 0,
    MOTOR_REVERSE
} MotorDirection_t;

void MotorDriver_Init(void);
void MotorDriver_Start(void);
void MotorDriver_Stop(void);
void MotorDriver_SetDirection(MotorDirection_t dir);

#endif // MOTOR_DRIVER_H
