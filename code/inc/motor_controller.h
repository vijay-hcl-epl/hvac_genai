#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    MOTOR_DIRECTION_NONE = 0,
    MOTOR_DIRECTION_FORWARD,
    MOTOR_DIRECTION_REVERSE
} MotorDirection_t;

void motor_controller_init(void);
void set_motor_state(MotorDirection_t direction, bool enable);

#endif // MOTOR_CONTROLLER_H
