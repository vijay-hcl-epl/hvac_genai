#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_FORWARD = 0U,
    MOTOR_REVERSE = 1U
} MotorDirection_t;

void Motor_Driver_Init(void);
void Motor_Driver_Drive(MotorDirection_t dir, bool enable);
void Motor_Driver_Stop(void);
bool Motor_Driver_Is_Active(void);

#endif // MOTOR_DRIVER_H
