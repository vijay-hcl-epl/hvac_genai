#include "CommandHandler.h"
#include "FlapControlLogic.h"
#include <stdint.h>

static uint8_t uart_rx_buffer[8];
static uint8_t target_position;

void UART_RX_Handler(uint8_t byte) {
    static uint8_t idx = 0;
    uart_rx_buffer[idx++] = byte;
    if (byte == '\n' || idx >= sizeof(uart_rx_buffer)) {
        ParseCommand(uart_rx_buffer, idx);
        idx = 0;
    }
}

void ParseCommand(const uint8_t* buffer, uint8_t length) {
    /* For simplicity, parse a digit '0'-'5' as target */
    if (length >= 2 && buffer[0] >= '0' && buffer[0] <= '5') {
        target_position = buffer[0] - '0';
        SetTargetPosition(target_position);
    }
}

void SetTargetPosition(uint8_t pos) {
    /* Pass to logic */
    DriveFlap();
}
