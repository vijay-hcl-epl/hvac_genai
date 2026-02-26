#include "hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Placeholder/mock implementation for porting
uint16_t hal_adc_read(void) {
    // Replace with actual ADC code
    // For unit testing, return a dummy value
    return 1200;
}

void hal_uart_read(uint8_t* data) {
    // Replace with actual UART receive
    *data = 0;
}

void hal_gpio_write(const char* name, int value) {
    // Replace with actual GPIO management
    // For demonstration
    printf("HAL: GPIO %s set to %d\n", name, value);
}

void hal_pwm_set(const char* name, int value) {
    // Replace with actual PWM management
    printf("HAL: PWM %s set to %d\n", name, value);
}
