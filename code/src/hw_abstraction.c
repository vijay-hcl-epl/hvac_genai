#include "hw_abstraction.h"
// Hardware register/config includes as per STM32F4/HAL headers
void hw_init(void) {
    // Initialize ADC, UART, GPIO, PWM; set initialized status.
}
uint16_t hw_adc_read(void) {
    // Trigger and return one ADC channel value
    return 0;
}
int hw_uart_read(uint8_t *rx) {
    // Read byte(s) from UART, store to rx, return count
    return 0;
}
void hw_uart_write(const uint8_t *tx, int len) {
    // Transmit tx buffer of len bytes over UART
}
void hw_gpio_set(uint8_t pin) {
    // Set specified GPIO pin
}
void hw_gpio_clear(uint8_t pin) {
    // Clear specified GPIO pin
}
void hw_pwm_set_duty(uint8_t channel, uint8_t percent) {
    // Set duty cycle for given channel
}
bool hw_is_initialized(void) {
    // Return TRUE if all peripherals initialized
    return true;
}
