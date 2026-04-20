#include "motor_control.h"
#include "config_data_store.h"

static bool motor_enabled = false;

void MotorControl_Init(void) {
    // configure output GPIOs/PWM as needed
    motor_enabled = false;
}

void MotorControl_MoveTo(int current, int target) {
    if (current < 0 || target < 0) return;
    if (current == target) {
        MotorControl_Stop();
        return;
    }
    // direction logic: assume increasing value = one direction
    if (target > current) {
        ConfigDataStore_SetMotorDir(1);
    } else {
        ConfigDataStore_SetMotorDir(0);
    }
    ConfigDataStore_SetMotorEnable(true);
    motor_enabled = true;
}

void MotorControl_Stop(void) {
    ConfigDataStore_SetMotorEnable(false);
    motor_enabled = false;
}
