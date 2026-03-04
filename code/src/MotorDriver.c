#include "MotorDriver.h"
#include <stdint.h>

static int8_t motor_enabled = 0;

void EnableMotor(int8_t direction) {
    /* Set GPIO/PWM for direction and enable output */
    motor_enabled = 1;
}

void DisableMotor(void) {
    /* Clear enable, set GPIOs to safe */
    motor_enabled = 0;
}
