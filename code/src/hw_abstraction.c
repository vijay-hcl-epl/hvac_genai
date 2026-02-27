#include "hw_abstraction.h"
#include <stdio.h>

// Stub/mock for HW, replace by MCU HAL functions.

uint16_t HWAbstraction_ReadADC(void) {
    // Replace with actual MCU ADC driver code
    return 1500; // Dummy value
}

void HWAbstraction_SetMotorDirection(motor_direction_t dir) {
    // Replace with GPIO output
    (void)dir;
}

void HWAbstraction_SetMotorPWM(uint8_t duty) {
    // Replace with Timer/PWM output
    (void)duty;
}

void HWAbstraction_SetPowerLED(bool on) {
    // Replace with GPIO control
    (void)on;
}

void HWAbstraction_SetPositionLED(uint8_t idx, bool on) {
    // Replace with GPIO control for LED 'idx'
    (void)idx;
    (void)on;
}
