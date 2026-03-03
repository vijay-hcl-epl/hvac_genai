#include "user_command_handler.h"
#include "calibration_config.h"
#include <string.h>

static char uart_rx_buffer[UART_RX_BUFFER_SIZE];
static uint16_t parsed_command_position = 0;
static bool new_command_pending = false;

// Simulate UART receive callback or polled RX
void user_command_handler_init(void) {
    memset(uart_rx_buffer, 0, UART_RX_BUFFER_SIZE);
    parsed_command_position = 0;
    new_command_pending = false;
}

// This would be called from a polling function or interrupt handler
default_weak void uart_receive_bytes(const char* bytes, uint8_t length);

void user_command_handler_rx(const char* bytes, uint8_t length) {
    if (length >= 1 && length < UART_RX_BUFFER_SIZE - 1) {
        memcpy(uart_rx_buffer, bytes, length);
        uart_rx_buffer[length] = '\0';
        char *endptr;
        int value = (int)strtol(uart_rx_buffer, &endptr, 10);
        if (*endptr == '\0') {
            if (value >= calibration_get_position_min() && value <= calibration_get_position_max()) {
                parsed_command_position = (uint16_t)value;
                new_command_pending = true;
            } else {
                new_command_pending = false;
            }
        } else {
            new_command_pending = false;
        }
    } else {
        new_command_pending = false;
    }
}

void user_command_handler_poll(void) {
    // Application would poll here and fill uart_rx_buffer as appropriate
    // For real HW, this would actually monitor UART HW buffer
}

bool get_new_command(uint16_t *target_position) {
    if (new_command_pending) {
        *target_position = parsed_command_position;
        new_command_pending = false;
        return true;
    }
    return false;
}
