#include "command_handler.h"
#include "position_control.h"
#include <ctype.h>

static uint8_t prev_command = 0xFF; // invalid value

void CommandHandler_Init(void)
{
    prev_command = 0xFF;
}

void CommandHandler_ProcessRxData(uint8_t rx_data)
{
    if (!isdigit(rx_data))
        return; // Not numeric
    uint8_t command = rx_data - '0';
    if (command > 5)
        return;
    if (command == prev_command)
        return; // Deduplicate
    prev_command = command;
    PositionControl_SetTarget(command);
}
