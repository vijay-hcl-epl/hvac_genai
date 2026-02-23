#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

typedef enum {
    MOTOR_DIRECTION_CW = 0,
    MOTOR_DIRECTION_CCW
} motor_direction_t;

void motor_driver_init(void);
void motor_driver_set_direction(motor_direction_t dir);
void motor_driver_enable(void);
void motor_driver_disable(void);

#endif // MOTOR_DRIVER_H
