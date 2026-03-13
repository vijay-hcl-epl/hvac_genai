#include "motor_driver_if.h"

void MotorDriverIF_Init(void) {
    // Initialize GPIOs/Timers
}

void MotorDriverIF_Drive(MotorDirection_t dir, uint8_t duty) {
    // Set direction pins, timer PWM duty (hardware specific)
    (void)dir; (void)duty;
}

void MotorDriverIF_Brake(void) {
    // Set both motor lines low (brake)
}

void MotorDriverIF_Off(void) {
    // Disable all motor outputs
}
