#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define CMD_BUFFER_SIZE 8

// Command Handler State
typedef enum {
    CMD_STATE_IDLE,
    CMD_STATE_RECEIVING,
    CMD_STATE_COMPLETE,
    CMD_STATE_ERROR
} cmd_state_t;

void CommandHandler_Init(void);
void CommandHandler_ReceiveChar(char c);
bool CommandHandler_IsCommandAvailable(void);
uint8_t CommandHandler_GetLastCommand(void);
void CommandHandler_Clear(void);

#endif // COMMAND_HANDLER_H
