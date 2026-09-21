#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

#define COMMAND_PARSER_POSITION_COUNT (4U)
#define COMMAND_PARSER_POSITION_MIN   (0U)
#define COMMAND_PARSER_POSITION_MAX   (3U)

typedef struct
{
    uint8_t position;
    uint8_t valid;
} CommandParser_CommandType;

void CommandParser_Init(void);
void CommandParser_AcceptRxByte(uint8_t rx_byte);
void CommandParser_Service(void);
CommandParser_CommandType CommandParser_GetLatestCommand(void);
uint8_t CommandParser_IsValidPosition(uint8_t position);

#endif /* COMMAND_PARSER_H */
