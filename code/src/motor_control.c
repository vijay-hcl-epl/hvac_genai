#include "motor_control.h"
#include <stm32f4xx_hal.h>
static uint8_t motor_enabled = 0U;
static MotorDir_t direction = MOTOR_DIR_OFF;
void MotorControl_Init(void) {
    /* STM32 GPIO/PWM init code placeholder */
    motor_enabled = 0U;
    direction = MOTOR_DIR_OFF;
}
void MotorControl_Start(MotorDir_t dir) {
    /* Set GPIO for direction, enable motor via PWM */
    direction = dir;
    motor_enabled = 1U;
}
void MotorControl_Stop(void) {
    /* Disable motor enable pin */
    motor_enabled = 0U;
    direction = MOTOR_DIR_OFF;
}
uint8_t MotorControl_IsActive(void) { return motor_enabled; }
