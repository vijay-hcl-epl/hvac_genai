#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>

// HAL abstraction functions
uint16_t hal_adc_read(void);
void hal_uart_read(uint8_t* data);
void hal_gpio_write(const char* name, int value);
void hal_pwm_set(const char* name, int value);

#endif // HAL_H
