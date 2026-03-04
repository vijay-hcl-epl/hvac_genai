#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>

void UART_RX_Handler(uint8_t byte);
void ParseCommand(const uint8_t* buffer, uint8_t length);
void SetTargetPosition(uint8_t pos);

#endif // COMMAND_HANDLER_H
