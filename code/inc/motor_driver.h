#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIR_STOP = 0,
    MOTOR_DIR_OPEN,
    MOTOR_DIR_CLOSE
} MotorDirection_t;

void motor_driver_init(void);
void motor_drive(MotorDirection_t dir, bool enable);
void motor_stop(void);
bool motor_get_status(void);

#endif // MOTOR_DRIVER_H
