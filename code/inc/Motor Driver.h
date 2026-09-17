#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

typedef enum
{
    MOTOR_DIRECTION_STOP = 0,
    MOTOR_DIRECTION_CLOSE,
    MOTOR_DIRECTION_OPEN
} Motor_Direction_t;

typedef struct
{
    Motor_Direction_t direction;
    uint8_t enabled;
    uint16_t duty;
} Motor_Status_t;

void Motor_Driver_Init(void);
void Motor_Driver_Drive(Motor_Direction_t direction, uint8_t enable);
void Motor_Driver_Stop(void);
Motor_Status_t Motor_Driver_Get_Status(void);

#endif
