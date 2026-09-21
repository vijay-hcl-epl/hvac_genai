#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

#define COMMAND_PARSER_POSITION_MIN   (0U)
#define COMMAND_PARSER_POSITION_MAX   (3U)

void CommandParser_Init(void);
void CommandParser_ProcessRxByte(uint8_t rx_byte);
uint8_t CommandParser_PollUart(void);
uint8_t CommandParser_GetLatestCommand(uint8_t * position);
uint8_t CommandParser_IsValidPosition(uint8_t position);

#endif /* COMMAND_PARSER_H */
