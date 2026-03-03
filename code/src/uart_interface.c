#include "uart_interface.h"
#include <string.h>

static UART_Status_t uart_status = { {0}, 0, false, false, false };

void UART_Init(void) {
    // Hardware-dependent UART initialization code stub
    uart_status.rx_count = 0;
    uart_status.rx_complete = false;
    uart_status.overflow = false;
    uart_status.error = false;
    memset(uart_status.rx_buffer, 0, UART_RX_BUFFER_SIZE);
}

uint8_t UART_ReadCmd(uint8_t *buf, uint8_t *len) {
    if (uart_status.rx_complete && !uart_status.error) {
        memcpy(buf, uart_status.rx_buffer, uart_status.rx_count);
        *len = uart_status.rx_count;
        uart_status.rx_complete = false;
        uart_status.rx_count = 0;
        memset(uart_status.rx_buffer, 0, UART_RX_BUFFER_SIZE);
        return 1;
    }
    return 0;
}

void UART_ClearBuffer(void) {
    uart_status.rx_count = 0;
    uart_status.rx_complete = false;
    uart_status.overflow = false;
    uart_status.error = false;
    memset(uart_status.rx_buffer, 0, UART_RX_BUFFER_SIZE);
}

const UART_Status_t* UART_GetStatus(void) {
    return &uart_status;
}

void UART_ISR_RX_Handler(uint8_t data) {
    // Simulated RX handler for single-byte arrival
    if (uart_status.rx_complete) {
        // Buffer full, command not consumed
        uart_status.overflow = true;
        return;
    }
    if (uart_status.rx_count < UART_RX_BUFFER_SIZE) {
        uart_status.rx_buffer[uart_status.rx_count++] = data;
        if (data == '\n' || uart_status.rx_count == UART_RX_BUFFER_SIZE) {
            uart_status.rx_complete = true;
        }
    } else {
        uart_status.overflow = true;
        uart_status.error = true;
    }
}
