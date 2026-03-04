#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>

typedef enum {
    FLAP_UP,
    FLAP_DOWN
} flap_dir_t;

void motor_control_init(void);
void motor_run(flap_dir_t dir);
void motor_stop(void);

#endif // MOTOR_CONTROL_H
