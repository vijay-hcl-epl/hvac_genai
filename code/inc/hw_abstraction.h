#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H
#include <stdint.h>
#include <stdbool.h>

void hw_init(void);
uint16_t hw_adc_read(void);
int hw_uart_read(uint8_t *rx); // Returns number of bytes read, 0 if none
void hw_uart_write(const uint8_t *tx, int len);
void hw_gpio_set(uint8_t pin);
void hw_gpio_clear(uint8_t pin);
void hw_pwm_set_duty(uint8_t channel, uint8_t percent); // 0-100%
bool hw_is_initialized(void);

#endif // HW_ABSTRACTION_H
