#include "uart_handler.h"
static volatile uint8_t command_buffer = 0;
static volatile bool rx_valid = false;
static volatile bool uart_error = false;
void uart_handler_init(void) { rx_valid = false; uart_error = false; }
void uart_rx_callback(uint8_t data) {
    if (data <= 5) {
        command_buffer = data;
        rx_valid = true;
    } else {
        uart_error = true;
        rx_valid = false;
    }
}
bool uart_get_valid_command(uint8_t *command_out) {
    if (rx_valid) {
        *command_out = command_buffer;
        rx_valid = false;
        return true;
    }
    return false;
}
void uart_clear_error(void) { uart_error = false; }
bool uart_has_error(void) { return uart_error; }
