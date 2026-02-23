#ifndef UART_CMD_H
#define UART_CMD_H

#include <stdint.h>
#include <stdbool.h>

void UARTCMD_Init(void);
void UARTCMD_Poll(void);
bool UARTCMD_IsCommandValid(void);
uint8_t UARTCMD_GetTargetPosition(void);
void UARTCMD_ClearCommand(void);

#endif /* UART_CMD_H */
