#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_COMMAND_POSITIONS 5

// Allowed positions can be adjusted as required
extern const uint8_t CommandParser_AllowedPositions[MAX_COMMAND_POSITIONS];

void CommandParser_Init(void);
void CommandParser_ProcessUART(void);
bool CommandParser_GetLatestCommand(uint8_t* cmd_pos);
bool CommandParser_HasValidCommand(void);
void CommandParser_ClearCommand(void);

#endif // COMMAND_PARSER_H
