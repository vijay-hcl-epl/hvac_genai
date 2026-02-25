#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIR_STOP = 0,
    MOTOR_DIR_CW = 1,
    MOTOR_DIR_CCW = 2
} MotorDirection_t;

void MotorController_Init(void);
void MotorController_Run(MotorDirection_t dir);
void MotorController_Stop(void);

#endif // MOTOR_CONTROLLER_H
