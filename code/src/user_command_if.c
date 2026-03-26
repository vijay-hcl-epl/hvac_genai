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
void UserCommandIF_RxHandler(uint8_t byte) {
    // UART/LIN receive ISR or poll handler
    // Very simplified logic, no real protocol parsing here
    if (byte <= 5) {
        cmd_value = byte;
        UserCommandIF_IssueACK();
    } else {
        error_count++;
        UserCommandIF_IssueNACK();
        ErrorHandler_SetError(ERROR_INVALID_CMD);
    }
}
void UserCommandIF_Process(void) {
    // Could be periodically called to process command
}
void UserCommandIF_IssueACK(void) {
    status_code = 0x00; // OK
    // emit OK on UART - placeholder
}
void UserCommandIF_IssueNACK(void) {
    status_code = 0xFF; // ERR
    // emit error on UART - placeholder
}
uint8_t UserCommandIF_GetLastCommand(void) {
    return cmd_value;
}
