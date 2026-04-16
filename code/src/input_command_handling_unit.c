#include "input_command_handling_unit.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Process UART commands from user
void input_command_resp_1(InputCommandData_t *data, const char *rx_data) {
    strncpy(data->uart_buffer, rx_data, UART_BUFFER_SIZE-1);
    data->uart_buffer[UART_BUFFER_SIZE-1] = '\0';

    // Parse numeric value and validate
    uint16_t pos = (uint16_t)atoi(data->uart_buffer);

    if (pos >= 0 && pos <= 1000) { // Example valid range, if LLD specifies explicitly use those boundaries
        data->flap_target = pos;
        data->command_valid = true;
    } else {
        data->command_valid = false;
    }
}

// Handle invalid user input
void input_command_resp_2(InputCommandData_t *data) {
    if (!data->command_valid) {
        memset(data->uart_buffer, 0, UART_BUFFER_SIZE);
    }
}
