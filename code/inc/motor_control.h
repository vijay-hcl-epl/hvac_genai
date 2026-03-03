#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIR_OPEN = 0,
    MOTOR_DIR_CLOSE
} MOTOR_Direction_t;

void MOTOR_Init(void);
void MOTOR_SetDirection(MOTOR_Direction_t dir);
void MOTOR_Enable(bool enable);
void MOTOR_Stop(void);

#endif // MOTOR_CONTROL_H
