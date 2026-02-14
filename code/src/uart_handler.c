#include "uart_handler.h"
static const uint8_t valid_commands[] = {0,1,2,3,4,5};
static uint8_t latest_cmd = 0;
static bool cmd_valid = false;
void UART_Handler_Init(void) {
    // Placeholder for UART peripheral initialization
}
void UART_Handler_RxISR(void) {
    // Simulated UART RX handler
    uint8_t rx = 0; // = uart_hw_read_byte();
    if (rx >= 0 && rx <= 5) {
        latest_cmd = rx;
        cmd_valid = true;
    } else {
        cmd_valid = false;
    }
}
void UART_GetCommand(uint8_t *value, bool *valid) {
    if (value && valid) {
        *value = latest_cmd;
        *valid = cmd_valid;
        cmd_valid = false;
    }
}
