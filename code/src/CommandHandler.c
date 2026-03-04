#include "CommandHandler.h"
#include "FlapControlLogic.h"
#include "UART.h"
#include "ErrorHandler.h"
static uint8_t rx_buffer[8];
static uint8_t buf_pos = 0;
void CommandHandler_Init(void) { buf_pos = 0; }
void CommandHandler_Process(void) {/* Typically nothing here for event-driven */}
void CommandHandler_OnUartRx(uint8_t byte) {
    if (byte == '\n') {
        // Basic validation: "P,<0-5>\n"
        if (rx_buffer[0] == 'P' && rx_buffer[1] == ',' && rx_buffer[2] >= '0' && rx_buffer[2] <= '5') {
            uint8_t pos = rx_buffer[2] - '0';
            FlapControlLogic_SetTarget(pos);
        } else {
            ErrorHandler_Report(1); // Invalid command format
        }
        buf_pos = 0;
    } else if(buf_pos < sizeof(rx_buffer)) {
        rx_buffer[buf_pos++] = byte;
    } else {
        buf_pos = 0; // Overflow/error
        ErrorHandler_Report(2);
    }
}
