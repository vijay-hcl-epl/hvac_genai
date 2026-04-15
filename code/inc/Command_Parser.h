#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

// Allowed positions (static table)
#define MAX_POSITION_COMMANDS   (4U)
extern const uint8_t allowed_positions[MAX_POSITION_COMMANDS];

typedef struct {
    uint8_t command_byte;
    bool is_valid;
} Command_t;

void Command_Parser_Init(void);
void Command_Parser_UART_Rx_Handler(uint8_t byte);
Command_t Command_Parser_Get_Latest(void);

#endif // COMMAND_PARSER_H
