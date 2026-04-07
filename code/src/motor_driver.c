#include "motor_driver.h"
#include <stm32f4xx.h>
static uint8_t motorState = 0; // 0=OFF, 1=ON
static int8_t direction = 0;
static uint8_t pwmVal = 200; // arbitrary
void MotorDriver_start(int8_t dir) {
    // Set GPIO, PWM ON (stub)
    direction = dir;
    motorState = 1;
    // TODO: Implement STM32F4 GPIOs & PWM control
}
void MotorDriver_stop(void) {
    // PWM OFF (stub)
    motorState = 0;
    // TODO: Implement STM32F4 PWM OFF
}
void motor_driver_init(void) {
    motorState = 0;
    direction = 0;
}
