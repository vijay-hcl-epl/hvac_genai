#ifndef UART_H
#define UART_H
#include <stdint.h>
void UART_Init(void);
void UART_Process(void);
void UART_SendResponse(uint8_t* data, uint8_t len);
void UART_Receive_ISR(void);
#endif
