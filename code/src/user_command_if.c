#include "user_command_if.h"
#include "error_handler.h"

static uint8_t cmd_buffer[8];
static uint8_t cmd_value;
static uint8_t status_code;
static uint8_t error_count;

void UserCommandIF_Init(void) {
    cmd_value = 0;
    status_code = 0;
    error_count = 0;
}

void UserCommandIF_RXHandler(uint8_t data) {
    // Dummy framing/parity check: value in range 0-5
    if (data <= 5) {
        cmd_value = data;
        UserCommandIF_SendAck();
        status_code = 0; // OK
    } else {
        error_count++;
        UserCommandIF_SendNack();
        status_code = 1; // ERR
        ErrorHandler_SetError(0x01); // CMD frame err
    }
}

void UserCommandIF_Process(void) {
    // Implement command processing as per state machine, called by main loop
    // For stub only
}

void UserCommandIF_SendAck(void) {
    // Send ACK over UART - STUB ONLY
}

void UserCommandIF_SendNack(void) {
    // Send NACK over UART - STUB ONLY
}

uint8_t UserCommandIF_GetCommand(void) {
    return cmd_value;
}

uint8_t UserCommandIF_GetStatus(void) {
    return status_code;
}
