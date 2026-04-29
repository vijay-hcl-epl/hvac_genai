#include "hardware_abstraction.h"
#include <stdio.h>
// Simulate hardware for demo only
static uint16_t simulated_adc_value = 123;
static bool motor_on = false;
static uint8_t led_status = 0x00;

void hardware_abstraction_init(void) {
    simulated_adc_value = 123;
    motor_on = false;
    led_status = 0x00;
}

uint16_t hardware_abstraction_adc_read(void) {
    // In real HW, perform proper ADC read
    return simulated_adc_value;
}

void hardware_abstraction_motor_set(bool enable) {
    motor_on = enable;
}

void hardware_abstraction_pwm_set(uint8_t step) {
    // Set PWM for position (no-op in sim)
    (void)step;
}

void hardware_abstraction_led_set(uint8_t led_pattern) {
    led_status = led_pattern;
}
