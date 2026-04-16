#include "InputHandlingUnit.h"

void InputHandlingUnit_resp_1() {
    // Responsibility: Handle commands entered by the user via UART interface to command the flap position.
    // Input Handling: Read from UART, parse.
    // State Handling: WaitForCommand / CommandParse.
    // Core Action: If valid, queue command.
    // Error Handling: On framing/packet/decode error, discard.
}

void InputHandlingUnit_resp_2() {
    // Responsibility: Safely ignore and discard invalid UART commands without acknowledgment or error.
    // Input Handling: Validate received data.
    // State Handling: CommandParse.
    // Core Action: Discard invalid or out-of-range commands.
    // Error Handling: Increment diagnostic error count, no outputs.
}
