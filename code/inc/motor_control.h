#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>

typedef enum { MOTOR_DIR_OFF = 0, MOTOR_DIR_FWD, MOTOR_DIR_REV } motor_direction_t;

void motor_control_init(void);
void motor_control_move(motor_direction_t dir);
void motor_control_stop(void);

#endif // MOTOR_CONTROL_H
