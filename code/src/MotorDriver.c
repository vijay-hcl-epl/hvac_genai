#include "MotorDriver.h"
#include "hw_abstraction.h"
void MotorDriver_Init(void) {
    /* Configures GPIO/PWM */ /* MISRA: Rule 2.2 – Empty function body should have a comment */
}
void MotorDriver_SetMotor(int8_t dir) {
    if (dir > 0) {
        hw_motor_forward();
    } else if (dir < 0) {
        hw_motor_reverse();
    } else {
        hw_motor_stop();
    }
}
