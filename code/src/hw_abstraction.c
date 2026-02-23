#include "hw_abstraction.h"

void hw_uart_init(void) {}
uint8_t hw_uart_read(void) { return 0; }
void hw_uart_write(uint8_t data) {(void)data; }

void hw_gpio_set(uint8_t pin, uint8_t value) { (void)pin; (void)value; }
uint16_t hw_adc_read(void) { return 0; }
void hw_pwm_enable(void) {}
void hw_pwm_disable(void) {}
