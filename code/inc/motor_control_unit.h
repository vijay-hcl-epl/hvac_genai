#ifndef MOTOR_CONTROL_UNIT_H
#define MOTOR_CONTROL_UNIT_H
#include <stdbool.h>

typedef enum {
    MOTOR_STOPPED,
    MOTOR_MOVING,
    MOTOR_ERROR
} motor_state_t;

typedef enum {
    MOTOR_DIR_FWD,
    MOTOR_DIR_REV,
    MOTOR_DIR_OFF
} motor_dir_t;

void motor_control_init(void);
void move_motor_to(int target_pos, motor_dir_t dir);
void stop_motor(void);
motor_state_t get_motor_status(void);

#endif
