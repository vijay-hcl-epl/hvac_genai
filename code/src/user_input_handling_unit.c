#include "user_input_handling_unit.h"
#include <string.h>
#include <ctype.h>

// Responsibility: Handle UART numeric input for flap position commands.
void user_input_handling_unit_resp_0(UserInputHandlingUnitData* data) {
    UserInputHandlingUnitState state = STATE_WAIT_FOR_INPUT;
    switch(state) {
        case STATE_WAIT_FOR_INPUT:
            // Poll/read UART input (stub: deterministically zeroed)
            memset(data->uart_rx_buffer, 0, UART_RX_BUFFER_SIZE);

            // Parse numeric command (stub: convert ASCII to int)
            int parsed_value = 0;
            int valid = 1;
            for (int i = 0; i < UART_RX_BUFFER_SIZE; ++i) {
                if (data->uart_rx_buffer[i] == 0) break;
                if (!isdigit(data->uart_rx_buffer[i])) {
                    valid = 0;
                    break;
                }
                parsed_value = parsed_value * 10 + (data->uart_rx_buffer[i] - '0');
            }

            // Error Handling: Non-numeric input (ignore)
            // Error Handling: Out-of-range value (ignore)
            if(!valid) {
                data->command_value = -1;
            } else {
                data->command_value = parsed_value;
            }
            break;
        default:
            break;
    }
}

// Responsibility: Validate and filter user input; ignore invalid commands without acknowledgment.
void user_input_handling_unit_resp_1(UserInputHandlingUnitData* data) {
    UserInputHandlingUnitState state = STATE_VALIDATE_INPUT;
    switch(state) {
        case STATE_VALIDATE_INPUT:
            // Validate value (stub: accept [0..7] only)
            if (data->command_value < 0 || data->command_value > 7) {
                // Out-of-range value (ignore)
                data->command_value = -1;
            }
            // Buffer overflow (flush) is not possible in deterministic fixed-length stub
            break;
        default:
            break;
    }
}
