#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

#define CMD_POSITION_INVALID ((uint8_t)0xFF)

void command_parser_init(void);
void command_parser_receive_byte(uint8_t byte);
bool command_parser_get_latest_command(uint8_t *position, bool *valid);

#endif // COMMAND_PARSER_H
