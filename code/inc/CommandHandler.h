/* CommandHandler.h - Responsible for receiving, validating, and interpreting UART user commands for flap positions. */
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define CMD_FLAP_POS_MIN    0
#define CMD_FLAP_POS_MAX    5

void CommandHandler_Init(void);
bool CommandHandler_ReceiveCommand(uint8_t* targetPos);
bool CommandHandler_Validate(uint8_t cmd, uint8_t* validCmd);

#endif /* COMMAND_HANDLER_H */
