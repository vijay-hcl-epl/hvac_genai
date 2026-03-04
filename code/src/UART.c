#include "UART.h"
#include "CommandHandler.h"
#include "ErrorHandler.h"
#include <stdint.h>
static uint8_t uart_rx_buf = 0;
void UART_Init(void) { }
void UART_Process(void) { }
void UART_SendResponse(uint8_t* data, uint8_t len) { }
void UART_Receive_ISR(void) {
    uint8_t rx = uart_rx_buf; // Would be read from HW in real system
    CommandHandler_OnUartRx(rx);
}
