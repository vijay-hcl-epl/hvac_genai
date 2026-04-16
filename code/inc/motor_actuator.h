#ifndef MOTOR_ACTUATOR_H
#define MOTOR_ACTUATOR_H
#include <stdint.h>
#include <stdbool.h>

typedef enum { DIR_CW = 0, DIR_CCW = 1 } MotorDirection;

void MotorActuator_Init(void);
void MotorActuator_Set(MotorDirection dir, bool enable);
void MotorActuator_Stop(void);

#endif // MOTOR_ACTUATOR_H
