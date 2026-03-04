#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
void CommandHandler_Init(void);
void CommandHandler_Process(void);
void CommandHandler_OnUartRx(uint8_t byte);
#endif
