#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

#define UART_RX_BUFFER_SIZE 32

typedef struct {
    uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
    uint8_t rx_count;
    bool rx_complete;
    bool overflow;
    bool error;
} UART_Status_t;

void UART_Init(void);
uint8_t UART_ReadCmd(uint8_t *buf, uint8_t *len);
void UART_ClearBuffer(void);
const UART_Status_t* UART_GetStatus(void);
void UART_ISR_RX_Handler(uint8_t data);

#endif // UART_INTERFACE_H
