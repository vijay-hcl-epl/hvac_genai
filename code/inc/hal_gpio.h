#ifndef HAL_GPIO_H
#define HAL_GPIO_H
#include <stdint.h>
void hal_gpio_set_dir_output(uint8_t pin);
void hal_gpio_write(uint8_t pin, uint8_t value);
#endif // HAL_GPIO_H
