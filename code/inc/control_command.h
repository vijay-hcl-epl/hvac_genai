#ifndef CONTROL_COMMAND_H
#define CONTROL_COMMAND_H

#include <stdint.h>

typedef enum {
    MOTOR_IDLE = 0,
    MOTOR_MOVING,
    MOTOR_STOPPED,
    MOTOR_ERROR
} motor_state_t;

void SetFlapPosition(int target_position);
void StopMotor(void);
void ControlCommandMain(void);

#endif // CONTROL_COMMAND_H
