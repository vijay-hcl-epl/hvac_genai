#include "user_command_interface.h"
#include <string.h>

// Example: valid positions from 0-4
const uint8_t valid_position_indices[NUM_FLAP_POSITIONS] = {0, 1, 2, 3, 4};

static uint8_t uart_cmd_buffer[UART_CMD_BUFFER_SIZE];
static uint8_t uart_cmd_index = 0;
static user_command_t latest_command = {0, false};

void user_command_interface_init(void)
{
    uart_cmd_index = 0;
    memset(uart_cmd_buffer, 0, UART_CMD_BUFFER_SIZE);
    latest_command.position_index = 0;
    latest_command.valid = false;
}

// Internal: checks if value is one of the valid indices
static bool is_valid_position(uint8_t idx)
{
    for (uint8_t i = 0; i < NUM_FLAP_POSITIONS; ++i) {
        if (valid_position_indices[i] == idx) return true;
    }
    return false;
}

void user_command_interface_receive_byte(uint8_t rx_byte)
{
    if (uart_cmd_index < UART_CMD_BUFFER_SIZE) {
        uart_cmd_buffer[uart_cmd_index++] = rx_byte;
        // Assume command is 1 ASCII digit [0-4], terminated by newline '\n'
        if (rx_byte == '\n') {
            // Try to parse command
            if (uart_cmd_index >= 2) {
                uint8_t digit = uart_cmd_buffer[0] - '0';
                if (is_valid_position(digit)) {
                    latest_command.position_index = digit;
                    latest_command.valid = true;
                } else {
                    latest_command.valid = false; // Invalid cmd
                }
            }
            uart_cmd_index = 0; // reset buffer
            memset(uart_cmd_buffer, 0, UART_CMD_BUFFER_SIZE);
        }
    } else {
        // Buffer overflow/reset
        uart_cmd_index = 0;
        memset(uart_cmd_buffer, 0, UART_CMD_BUFFER_SIZE);
        latest_command.valid = false;
    }
}

user_command_t get_user_command(void)
{
    return latest_command;
}
