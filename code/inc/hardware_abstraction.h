#ifndef HARDWARE_ABSTRACTION_H
#define HARDWARE_ABSTRACTION_H

#include <stdint.h>
#include <stdbool.h>

// API: Init all hardware
void hardware_abstraction_init(void);
// API: Read ADC value (returns raw ADC)
uint16_t hardware_abstraction_adc_read(void);
// API: Set actuator/motor
void hardware_abstraction_motor_set(bool enable);
// API: Set flap PWM for target
void hardware_abstraction_pwm_set(uint8_t step);
// API: Set LED status
void hardware_abstraction_led_set(uint8_t led_pattern);

#endif // HARDWARE_ABSTRACTION_H
