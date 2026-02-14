#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H
#include <stdint.h>
#include <stdbool.h>
// Motor
void hw_motor_forward(void);
void hw_motor_reverse(void);
void hw_motor_stop(void);
// ADC
uint16_t hw_adc_read(void);
// LEDs
void hw_set_led(uint8_t index, bool on);
void hw_init_leds(void);
void hw_set_power_led(bool on);
#endif // HW_ABSTRACTION_H
