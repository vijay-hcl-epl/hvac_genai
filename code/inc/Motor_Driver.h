#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIR_FORWARD = 0,
    MOTOR_DIR_REVERSE = 1
} MotorDirection_t;

void MotorDriver_Init(void);
void MotorDriver_Drive(MotorDirection_t direction, bool enable);
void MotorDriver_Stop(void);
bool MotorDriver_IsActive(void);

#endif // MOTOR_DRIVER_H
