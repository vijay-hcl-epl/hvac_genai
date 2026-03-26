#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIRECTION_STOP = 0,
    MOTOR_DIRECTION_OPEN,
    MOTOR_DIRECTION_CLOSE,
} MotorDirection;

void set_motor_direction(MotorDirection dir);
bool is_motor_engaged(void);

#endif // MOTOR_CONTROL_H
