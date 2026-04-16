#include "motor_actuator.h"
#include <stdint.h>
// HW driver mocks (to be replaced)
static void GPIO_SetDirection(MotorDirection dir) { (void)dir; }
static void PWM_Enable(bool en) { (void)en; }
static void GPIO_MotorEnable(bool en) { (void)en; }

static bool motor_enable = false;
static MotorDirection motor_dir = DIR_CW;

void MotorActuator_Init(void) {
    motor_enable = false;
    motor_dir = DIR_CW;
    GPIO_MotorEnable(false);
    PWM_Enable(false);
}

void MotorActuator_Set(MotorDirection dir, bool enable) {
    motor_dir = dir;
    motor_enable = enable;
    GPIO_SetDirection(dir);
    GPIO_MotorEnable(enable);
    PWM_Enable(enable);
}

void MotorActuator_Stop(void) {
    motor_enable = false;
    GPIO_MotorEnable(false);
    PWM_Enable(false);
}
