#include "motor_control.h"
#include <stdio.h>// for demonstration (no real GPIO)
#define MOTOR_DIR_PIN 1
#define MOTOR_EN_PIN 2
static bool motor_enabled = false;
static uint8_t motor_direction = 0;

void MotorCtrl_Set(uint8_t dir, bool enable) {
    motor_direction = dir;
    motor_enabled = enable;
    // Stub: Replace with GPIO operations. For demo, print.
    // printf("Motor set: direction=%d, enable=%d\n", dir, enable);
}

void MotorCtrl_Stop(void) {
    motor_enabled = false;
    // printf("Motor stopped\n");
}
