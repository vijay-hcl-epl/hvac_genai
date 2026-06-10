#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include "flap_control_coordinator.h"

void Enable_Motor(direction_t dir);
void Disable_Motor(void);

#endif // MOTOR_CONTROL_H
