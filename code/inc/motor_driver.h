#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

// Directions
typedef enum {
    MOTOR_DIR_FWD,
    MOTOR_DIR_REV
} motor_dir_t;

// API
void motor_init(void);
void motor_drive(motor_dir_t dir, bool enable);
void motor_stop(void);
bool motor_get_status(void);

#endif // MOTOR_DRIVER_H
