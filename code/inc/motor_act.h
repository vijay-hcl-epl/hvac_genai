#ifndef MOTOR_ACT_H
#define MOTOR_ACT_H
#include <stdint.h>

// Direction: 1=FWD, 0=REV
int motor_move(uint8_t direction);
void motor_stop(void);

#endif // MOTOR_ACT_H
