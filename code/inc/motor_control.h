#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include "flap_controller.h"

void MotorControl_Init(void);
void MotorControl_ApplyOrder(ControlOrder_t order);

#endif // MOTOR_CONTROL_H
