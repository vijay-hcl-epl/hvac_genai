#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/* Allowed commands: update this table if more positions needed */
#define CMD_MAX_POSITIONS 5

typedef struct {
    uint8_t command;
    bool valid;
} CommandParser_Cmd_t;

void CommandParser_Init(void);
void CommandParser_UARTCallback(uint8_t data);
CommandParser_Cmd_t CommandParser_GetLatestCommand(void);

#endif /* COMMAND_PARSER_H */
