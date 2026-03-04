/* MotorDriver.h - Interface for controlling the DC motor, direction, and enable/disable. */
#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

#define MOTOR_DIR_UP    1
#define MOTOR_DIR_DOWN  0

void MotorDriver_Init(void);
void MotorDriver_CmdActuate(uint8_t direction);
void MotorDriver_Stop(void);

#endif /* MOTOR_DRIVER_H */
