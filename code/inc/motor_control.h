#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>
#include <stdbool.h>
void MOTC_Actuate(uint8_t direction, bool enable);
void MOTC_Stop(void);
#endif // MOTOR_CONTROL_H
