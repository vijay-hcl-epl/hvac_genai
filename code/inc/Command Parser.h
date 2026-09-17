#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

void Command_Parser_Init(void);
void Command_Parser_Update(void);
void Command_Parser_Get_Latest_Command(uint8_t * position, uint8_t * valid);
void Command_Parser_Clear_Command(void);

#endif
