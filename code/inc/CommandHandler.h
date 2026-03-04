#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
#include <stdbool.h>

void CommandHandler_Init(void);
void CommandHandler_ProcessRx(uint8_t byte);
bool CommandHandler_GetLatestCommand(uint8_t *pos);

#endif // COMMAND_HANDLER_H
