#include "motor_control.h"
#include "hardware_abstraction.h"

static enum {Motor_Stopped, Motor_MovingCW, Motor_MovingCCW} motor_state = Motor_Stopped;
static bool error_flag = false;

void Enable_Motor(direction_t dir) {
    if (motor_state != Motor_Stopped) return;
    if (dir == DIR_CW) {
        PWM_Set(0, 100); // Example: channel 0, full speed CW
    } else {
        PWM_Set(0, 100); // Example: channel 0, full speed CCW
    }
    motor_state = (dir == DIR_CW) ? Motor_MovingCW : Motor_MovingCCW;
    GPIO_Write(1, true); // Enable motor output
}

void Disable_Motor(void) {
    PWM_Set(0, 0);
    GPIO_Write(1, false);
    motor_state = Motor_Stopped;
    error_flag = false;
}
