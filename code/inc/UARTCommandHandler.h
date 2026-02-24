#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

// UART Command Handler APIs
void UARTCommandHandler_Init(void);
void UARTCommandHandler_RxISR(uint8_t rxChar);
bool UARTCommandHandler_HasNewCmd(void);
uint8_t UARTCommandHandler_GetCmd(void);
void UARTCommandHandler_ClearFlag(void);

#endif // UART_COMMAND_HANDLER_H
