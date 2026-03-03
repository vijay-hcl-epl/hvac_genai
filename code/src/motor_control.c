#include "motor_control.h"
#include <stdint.h>
#include <stdbool.h>

static MOTOR_Direction_t motor_dir = MOTOR_DIR_OPEN;
static bool motor_enabled = false;

void MOTOR_Init(void) {
    motor_dir = MOTOR_DIR_OPEN;
    motor_enabled = false;
    // Hardware init code for GPIO/PWM stub
}

void MOTOR_SetDirection(MOTOR_Direction_t dir) {
    motor_dir = dir;
    // Hardware GPIO direction set
}

void MOTOR_Enable(bool enable) {
    motor_enabled = enable;
    // Hardware GPIO or PWM enable output
}

void MOTOR_Stop(void) {
    motor_enabled = false;
    // Hardware GPIO/PWM disable / all outputs off
}
