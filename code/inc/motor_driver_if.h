#ifndef MOTOR_DRIVER_IF_H
#define MOTOR_DRIVER_IF_H

#include <stdint.h>

typedef enum {
    MOTOR_DIR_NONE = 0,
    MOTOR_DIR_CW,
    MOTOR_DIR_CCW
} MotorDirection_t;

void MotorDriverIF_Init(void);
void MotorDriverIF_Drive(MotorDirection_t dir, uint8_t duty);
void MotorDriverIF_Brake(void);
void MotorDriverIF_Off(void);

#endif // MOTOR_DRIVER_IF_H
