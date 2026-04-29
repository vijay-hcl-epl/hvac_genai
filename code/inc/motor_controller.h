#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H
#include <stdint.h>
#include <stdbool.h>

void motor_set(uint8_t target, uint8_t current, bool valid);
void motor_stop(void);

#endif // MOTOR_CONTROLLER_H
