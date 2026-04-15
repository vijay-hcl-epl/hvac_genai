#include "Command_Parser.h"
#include <string.h>

static Command_t latest_cmd = {0};
const uint8_t allowed_positions[MAX_POSITION_COMMANDS] = {0x10, 0x20, 0x30, 0x40}; // Example positions

void Command_Parser_Init(void)
{
    latest_cmd.command_byte = 0U;
    latest_cmd.is_valid = false;
}

static bool is_allowed_command(uint8_t cmd)
{
    for(uint8_t i = 0; i < MAX_POSITION_COMMANDS; ++i)
    {
        if(cmd == allowed_positions[i])
            return true;
    }
    return false;
}

void Command_Parser_UART_Rx_Handler(uint8_t byte)
{
    if(is_allowed_command(byte))
    {
        latest_cmd.command_byte = byte;
        latest_cmd.is_valid = true;
    }
    else
    {
        latest_cmd.command_byte = 0U;
        latest_cmd.is_valid = false;
    }
}

Command_t Command_Parser_Get_Latest(void)
{
    return latest_cmd;
}
