#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

#define MOTOR_DRIVER_DIR_STOP     (0U)
#define MOTOR_DRIVER_DIR_REVERSE  (1U)
#define MOTOR_DRIVER_DIR_FORWARD  (2U)

typedef struct
{
    uint8_t direction;
    uint8_t enabled;
    uint16_t duty_percent;
} MotorDriver_StatusType;

void MotorDriver_Init(void);
void MotorDriver_DriveMotor(uint8_t direction, uint8_t enable);
void MotorDriver_StopMotor(void);
MotorDriver_StatusType MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
