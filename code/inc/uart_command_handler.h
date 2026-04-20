#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H

#include <stdbool.h>
#include <stdint.h>

#define UART_CMD_MIN      0
#define UART_CMD_MAX      5
#define UART_RX_BUF_LEN   8

void UART_CommandHandler_Init(void);
void UART_CommandHandler_ReceiveChar(char c);
bool UART_CommandHandler_GetValidCommand(int *cmd_out);
bool UART_CommandHandler_IsBusy(void);
void UART_CommandHandler_Reset(void);

#endif // UART_COMMAND_HANDLER_H
