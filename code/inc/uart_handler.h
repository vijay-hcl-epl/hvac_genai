#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include <stdint.h>
#include <stddef.h>

#define UART_RX_BUFFER_SIZE 32

typedef enum {
    UART_STATE_IDLE = 0,
    UART_STATE_RECEIVING,
    UART_STATE_FRAME_COMPLETE,
    UART_STATE_ERROR
} UartHandlerState_t;

void UART_Handler_Init(void);
void UART_Handler_RxISR(uint8_t byte);
int UART_Handler_GetParsedCommand(uint8_t* buf, size_t* len);

#endif // UART_HANDLER_H
