#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
#include <stdbool.h>
#include "SystemTypes.h"

void CommandHandler_Init(void);
void CommandHandler_UART_ByteReceived(uint8_t byte);

#endif // COMMAND_HANDLER_H
