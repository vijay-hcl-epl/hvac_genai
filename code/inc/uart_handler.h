#ifndef UART_HANDLER_H
#define UART_HANDLER_H
#include <stdbool.h>
#include <stdint.h>
void UART_Handler_Init(void);
void UART_Handler_RxISR(void);
void UART_GetCommand(uint8_t *value, bool *valid);
#endif // UART_HANDLER_H
