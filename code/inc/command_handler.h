#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdbool.h>
#include <stdint.h>

#define CMD_HANDLER_RX_BUF_SIZE 8

void CommandHandler_Init(void);
void CommandHandler_UART_RxCallback(const uint8_t *rx_buf, uint16_t len);
bool CommandHandler_GetLastCommand(int *value);
bool CommandHandler_IsValid(void);

#endif // COMMAND_HANDLER_H
