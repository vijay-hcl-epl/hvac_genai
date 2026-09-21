#include "Command Parser.h"
#include "stm32f4xx_hal.h"

/* UART command handling for single-byte latest-wins command queue.
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022.
 */

extern UART_HandleTypeDef huart2;

typedef struct
{
    uint8_t command_byte;
    Hvac_FlapPosition_t position;
} CommandParser_MapEntry_t;

static const CommandParser_MapEntry_t CommandParser_AllowedMap[] =
{
    { (uint8_t)'0', HVAC_FLAP_POSITION_FACE },
    { (uint8_t)'1', HVAC_FLAP_POSITION_BI_LEVEL },
    { (uint8_t)'2', HVAC_FLAP_POSITION_FOOT },
    { (uint8_t)'3', HVAC_FLAP_POSITION_DEFROST }
};

static CommandParser_State_t CommandParser_State = COMMAND_PARSER_STATE_INIT;
static CommandParser_Command_t CommandParser_LatestCommand =
{
    false,
    HVAC_FLAP_POSITION_INVALID,
    0U
};

static bool CommandParser_MapByte(uint8_t raw_byte, Hvac_FlapPosition_t * position)
{
    bool mapped = false;
    uint32_t index;

    if (position != (Hvac_FlapPosition_t *)0)
    {
        for (index = 0U; index < (sizeof(CommandParser_AllowedMap) / sizeof(CommandParser_AllowedMap[0])); index++)
        {
            if (CommandParser_AllowedMap[index].command_byte == raw_byte)
            {
                *position = CommandParser_AllowedMap[index].position;
                mapped = true;
                break;
            }
        }
    }

    return mapped;
}

void CommandParser_Init(void)
{
    CommandParser_State = COMMAND_PARSER_STATE_WAIT_RX;
    CommandParser_LatestCommand.valid = false;
    CommandParser_LatestCommand.position = HVAC_FLAP_POSITION_INVALID;
    CommandParser_LatestCommand.raw_byte = 0U;
}

void CommandParser_Task(void)
{
    uint8_t received_byte = 0U;
    Hvac_FlapPosition_t mapped_position = HVAC_FLAP_POSITION_INVALID;
    HAL_StatusTypeDef hal_status;

    hal_status = HAL_UART_Receive(&huart2, &received_byte, 1U, 0U);
    if (hal_status == HAL_OK)
    {
        if (CommandParser_MapByte(received_byte, &mapped_position) == true)
        {
            if ((CommandParser_LatestCommand.valid == false) ||
                (CommandParser_LatestCommand.position != mapped_position))
            {
                CommandParser_LatestCommand.valid = true;
                CommandParser_LatestCommand.position = mapped_position;
                CommandParser_LatestCommand.raw_byte = received_byte;
            }
            CommandParser_State = COMMAND_PARSER_STATE_VALID;
        }
        else
        {
            CommandParser_State = COMMAND_PARSER_STATE_INVALID;
        }
    }
    else
    {
        CommandParser_State = COMMAND_PARSER_STATE_WAIT_RX;
    }
}

CommandParser_Command_t CommandParser_GetLatestCommand(void)
{
    return CommandParser_LatestCommand;
}

void CommandParser_ClearLatestCommand(void)
{
    CommandParser_LatestCommand.valid = false;
    CommandParser_LatestCommand.position = HVAC_FLAP_POSITION_INVALID;
    CommandParser_LatestCommand.raw_byte = 0U;
    CommandParser_State = COMMAND_PARSER_STATE_WAIT_RX;
}

CommandParser_State_t CommandParser_GetState(void)
{
    return CommandParser_State;
}
