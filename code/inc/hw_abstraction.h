#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H

#include <stdint.h>
#include <stdbool.h>

void hal_uart_init(void);
bool hal_uart_rx_ready(void);
uint8_t hal_uart_read(void);
void hal_uart_write(uint8_t val);
void hal_gpio_set(uint8_t pin);
void hal_gpio_clear(uint8_t pin);
uint16_t hal_adc_get_value(uint8_t channel);
void hal_pwm_enable(void);
void hal_pwm_disable(void);

#endif // HW_ABSTRACTION_H
