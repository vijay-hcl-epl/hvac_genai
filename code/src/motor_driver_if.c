#include "motor_driver_if.h"
#include "error_handler.h"

void MotorDriverIF_Init(void) {}

void MotorDriverIF_Drive(uint8_t direction, uint8_t duty) {
    // Stubbed: set PWM and direction
}

void MotorDriverIF_Brake(void) {
    // Stub: brake
}

void MotorDriverIF_Off(void) {
    // Stub: disable output
}
