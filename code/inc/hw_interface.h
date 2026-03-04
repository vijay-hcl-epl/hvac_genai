#ifndef HW_INTERFACE_H
#define HW_INTERFACE_H
#include <stdint.h>

// Pin aliases
#define GPIO_MOTOR_CW   (0)
#define GPIO_MOTOR_CCW  (1)

void hw_interface_init(void);
void gpio_set(uint8_t pin);
void gpio_clear(uint8_t pin);
uint16_t adc_read(void);
uint8_t uart_read(void);

#endif // HW_INTERFACE_H
