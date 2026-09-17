#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdbool.h>
#include <stdint.h>

void Command_Parser_Init(void);
void Command_Parser_Update(void);
bool Command_Parser_GetLatestCommand(uint8_t * position);
void Command_Parser_Clear(void);

#endif /* COMMAND_PARSER_H */
