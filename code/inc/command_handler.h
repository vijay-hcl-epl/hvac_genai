#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
#define CMD_INVALID (-1)
int CommandHandler_GetValidCommand(void);
void CommandHandler_UartRxHandler(uint8_t data);
void CommandHandler_Init(void);
#endif /* COMMAND_HANDLER_H */
