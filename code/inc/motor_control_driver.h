#ifndef MOTOR_CONTROL_DRIVER_H
#define MOTOR_CONTROL_DRIVER_H
#include <stdint.h>

typedef enum {
    MOTOR_DIRECTION_OFF = 0,
    MOTOR_DIRECTION_FORWARD,
    MOTOR_DIRECTION_REVERSE
} motor_direction_t;

void motor_control_driver_set_direction(motor_direction_t direction);
void motor_control_driver_disable(void);
void motor_control_driver_init(void);

#endif // MOTOR_CONTROL_DRIVER_H
