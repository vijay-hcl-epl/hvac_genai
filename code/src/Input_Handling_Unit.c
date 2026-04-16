#include "Input_Handling_Unit.h"
// Responsibility 1: Parse and interpret user flap position commands received via UART.
void Input_Handling_Unit_resp_1(InputHandlingUnitData* data) {
    // TRACE: "Receive data into buffer, scan delimiter/length."
    data->uart_buffer[0] = 0; // Placeholder for actual UART RX logic.
}
// Responsibility 2: Validate incoming command values for correctness.
void Input_Handling_Unit_resp_2(InputHandlingUnitData* data) {
    // TRACE: "Parse numeric value; compare to valid range."
    if (data->uart_buffer[0] <= 5) {
        data->parsed_command = data->uart_buffer[0];
        data->is_valid = 1;
        data->ignore_flag = 0;
    } else {
        data->is_valid = 0;
        data->ignore_flag = 1;
        data->consecutive_invalid++;
        if(data->consecutive_invalid >= 5) {
            // ALERT: Max 5 ignored consecutive commands before alert
        }
    }
}
// Responsibility 3: Ignore invalid commands and suppress acknowledgment per requirements.
void Input_Handling_Unit_resp_3(InputHandlingUnitData* data) {
    // TRACE: "If invalid, set ignore flag and do not trigger acknowledgment."
    // Handled in Responsibility 2
}
