#ifndef MOTOR_DRIVER_INTERFACE_H
#define MOTOR_DRIVER_INTERFACE_H
#include <stdint.h>

typedef enum {
    MOTOR_DIR_FORWARD = 0,
    MOTOR_DIR_REVERSE
} motor_dir_t;

void motor_driver_interface_init(void);
void motor_driver_interface_set_motor(motor_dir_t dir, uint8_t duty);
void motor_driver_interface_stop_motor(void);

#endif // MOTOR_DRIVER_INTERFACE_H
