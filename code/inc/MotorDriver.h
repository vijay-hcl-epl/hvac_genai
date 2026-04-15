#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIR_STOP = 0,
    MOTOR_DIR_FORWARD,
    MOTOR_DIR_REVERSE
} MotorDriver_Direction_t;

void MotorDriver_Init(void);
void MotorDriver_Drive(MotorDriver_Direction_t dir, uint8_t pwm);
void MotorDriver_Stop(void);
bool MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
