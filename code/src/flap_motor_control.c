#include "flap_motor_control.h"
#include "position_feedback.h"
#include "error_handler.h"
#include <stdio.h>
static uint8_t target_position = 0;
static uint8_t motor_state = 0; // 0:IDLE 1:MOVING 2:ERROR
void FlapMotorControl_Init(void) {
    target_position = 0;
    motor_state = 0;
}
void FlapMotorControl_MoveTo(uint8_t target) {
    uint8_t current = GetCurrentFlapPosition();
    if (current == target) {
        FlapMotorControl_Stop();
        return;
    }
    target_position = target;
    motor_state = 1;
    // Start motor in direction (pseudo)
}
void FlapMotorControl_Update(void) {
    if (motor_state == 1) {
        uint8_t curr = GetCurrentFlapPosition();
        if (curr == target_position) {
            FlapMotorControl_Stop();
        }
    }
}
void FlapMotorControl_Stop(void) {
    // Disable GPIO/PWM
    motor_state = 0;
}
