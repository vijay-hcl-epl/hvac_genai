#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>
void start_motor(uint8_t direction, uint16_t pwm);
void stop_motor(void);
#endif // MOTOR_CONTROL_H
