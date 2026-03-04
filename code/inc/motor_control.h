#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>

/** Motor output states */
typedef enum {
    MOTOR_STATE_DISABLED,
    MOTOR_STATE_FWD,
    MOTOR_STATE_REV
} motor_state_t;

/** Direction, FWD or REV */
typedef enum {
    MOTOR_DIR_FWD,
    MOTOR_DIR_REV
} motor_dir_t;

/** Command the motor to move in a direction. */
void motor_control_move(motor_dir_t dir);

/** Stop the motor (disable outputs). */
void motor_control_stop(void);

/** Returns motor status. */
int motor_control_status(void);

/** Register a motor fault condition. */
void motor_control_fault(void);

#endif // MOTOR_CONTROL_H
