#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#define MOTOR_DRIVER_DIR_STOP  (0U)
#define MOTOR_DRIVER_DIR_OPEN  (1U)
#define MOTOR_DRIVER_DIR_CLOSE (2U)

typedef struct
{
    uint8_t direction;
    bool enabled;
    uint16_t pwm_duty;
} Motor_Driver_StatusType;

void Motor_Driver_Init(void);
void Motor_Driver_DriveMotor(uint8_t direction, bool enable);
void Motor_Driver_StopMotor(void);
Motor_Driver_StatusType Motor_Driver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
