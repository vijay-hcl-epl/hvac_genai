#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

void CommandHandler_Init(void);
void CommandHandler_ProcessRxData(uint8_t rx_data);

#endif // COMMAND_HANDLER_H
