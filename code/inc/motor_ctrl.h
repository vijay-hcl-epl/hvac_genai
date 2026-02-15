#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H
#include <stdint.h>

#define MOTOR_DIR_CW  1U
#define MOTOR_DIR_CCW 0U
void motor_ctrl_init(void);
void motor_ctrl_start(uint8_t dir);
void motor_ctrl_stop(void);

#endif // MOTOR_CTRL_H
