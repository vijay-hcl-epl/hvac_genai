#include "Command_Parser.h"
#include "stm32f4xx_hal.h"

static uint8_t latest_command_position = 0;
static bool command_valid = false;

// Allowed flap positions (example: 0..4)
const uint8_t CommandParser_AllowedPositions[MAX_COMMAND_POSITIONS] = {0, 1, 2, 3, 4};

void CommandParser_Init(void)
{
    latest_command_position = 0;
    command_valid = false;
}

// Internal: Validate incoming command
static bool is_position_allowed(uint8_t pos)
{
    for (uint8_t i = 0; i < MAX_COMMAND_POSITIONS; ++i) {
        if (CommandParser_AllowedPositions[i] == pos) {
            return true;
        }
    }
    return false;
}

// Example UART byte reading; replace with HAL_UART_Receive if needed
static bool UART_GetByte(uint8_t* rx_byte)
{
    // Example: blocking receive in this mockup (replace for ISR or buffered real impl)
    if (HAL_UART_Receive(&huart2, rx_byte, 1, 0) == HAL_OK) {
        return true;
    }
    return false;
}

void CommandParser_ProcessUART(void)
{
    uint8_t rx;
    if (UART_GetByte(&rx)) {
        if (is_position_allowed(rx)) {
            if ((!command_valid) || (latest_command_position != rx)) {
                latest_command_position = rx;
                command_valid = true;
            }
        } else {
            // Invalid command, ignore
            command_valid = false;
        }
    }
}

bool CommandParser_GetLatestCommand(uint8_t* cmd_pos)
{
    if (command_valid) {
        *cmd_pos = latest_command_position;
        return true;
    }
    return false;
}

bool CommandParser_HasValidCommand(void)
{
    return command_valid;
}

void CommandParser_ClearCommand(void)
{
    command_valid = false;
}
