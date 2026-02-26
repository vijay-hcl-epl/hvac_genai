#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdbool.h>

typedef enum {
    MOTOR_OFF = 0,
    MOTOR_FORWARD,
    MOTOR_REVERSE
} motor_direction_t;

void motor_driver_init(void);
void motor_driver_actuate(motor_direction_t direction);
void motor_driver_stop(void);
bool motor_driver_is_enabled(void);

#endif // MOTOR_DRIVER_H
