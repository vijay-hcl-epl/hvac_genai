#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H

#include <stdint.h>

// Platform-specific pin definitions and API prototypes
#define MOTOR_DIR_PIN      (1)
#define POWER_LED_PIN      (2)
#define POS_LED_PIN_0      (3)
#define POS_LED_PIN_1      (4)
#define POS_LED_PIN_2      (5)
#define POS_LED_PIN_3      (6)
#define POS_LED_PIN_4      (7)
#define POS_LED_PIN_5      (8)

void hw_uart_init(void);
uint8_t hw_uart_read(void);
void hw_uart_write(uint8_t data);

void hw_gpio_set(uint8_t pin, uint8_t value);

uint16_t hw_adc_read(void);
void hw_pwm_enable(void);
void hw_pwm_disable(void);

#endif // HW_ABSTRACTION_H
