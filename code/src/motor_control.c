// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf CCU6 (18.10), BDRV_CTRL1 (27.4)
#include "motor_control.h"
#include "error_handler.h"
#define CCU6_T12PR (*(volatile unsigned int*)0x40010008)
#define CCU6_T12 (*(volatile unsigned int*)0x40010000)
#define CCU6_T12CH1 (*(volatile unsigned int*)0x4001000C)
#define BDRV_CTRL1 (*(volatile unsigned int*)0x40016000)
void IMotorControl_start(uint8_t direction, uint16_t pwm) {
    // Enable H-Bridge via BDRV_CTRL1, set direction
    if (direction == 0) {
        BDRV_CTRL1 = (1<<16) | (1<<8); // enable HS1+LS2
    } else {
        BDRV_CTRL1 = (1<<0) | (1<<8); // enable LS1+LS2
    }
    // Configure PWM
    CCU6_T12PR = pwm;  // period
    CCU6_T12CH1 = pwm/2; // duty 50%
}
void IMotorControl_stop(void) {
    // Brake: set both LS or both HS
    BDRV_CTRL1 = (1<<16) | (1<<0); // brake mode
    CCU6_T12PR = 0;
    CCU6_T12CH1 = 0;
}
