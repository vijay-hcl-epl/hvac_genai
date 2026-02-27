#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

typedef enum {
    MOTOR_DIRECTION_FWD = 0,
    MOTOR_DIRECTION_REV = 1
} motor_direction_t;

void MotorDriver_Init(void);
void MotorDriver_Enable(motor_direction_t dir);
void MotorDriver_Disable(void);

#endif // MOTOR_DRIVER_H
