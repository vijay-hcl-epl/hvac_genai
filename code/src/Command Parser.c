#include "Command Parser.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

typedef enum
{
    COMMAND_STATE_INIT = 0,
    COMMAND_STATE_WAIT_RX,
    COMMAND_STATE_VALID,
    COMMAND_STATE_INVALID
} CommandParser_StateType;

typedef struct
{
    uint8_t latest_position;
    uint8_t valid;
    CommandParser_StateType state;
} CommandParser_ContextType;

static CommandParser_ContextType command_context;
static const uint8_t command_position_table[4] = {0U, 1U, 2U, 3U};

static uint8_t CommandParser_MapByte(uint8_t rx_byte, uint8_t * position)
{
    uint8_t result = 0U;

    if ((rx_byte >= (uint8_t)'0') && (rx_byte <= (uint8_t)'3'))
    {
        *position = (uint8_t)(rx_byte - (uint8_t)'0');
        result = 1U;
    }
    else if (rx_byte <= COMMAND_PARSER_POSITION_MAX)
    {
        *position = rx_byte;
        result = 1U;
    }
    else
    {
        result = 0U;
    }

    return result;
}

void CommandParser_Init(void)
{
    command_context.latest_position = 0U;
    command_context.valid = 0U;
    command_context.state = COMMAND_STATE_WAIT_RX;
}

uint8_t CommandParser_IsValidPosition(uint8_t position)
{
    uint8_t idx;
    uint8_t valid = 0U;

    for (idx = 0U; idx < 4U; idx++)
    {
        if (position == command_position_table[idx])
        {
            valid = 1U;
        }
    }

    return valid;
}

void CommandParser_ProcessRxByte(uint8_t rx_byte)
{
    uint8_t mapped_position = 0U;

    if (CommandParser_MapByte(rx_byte, &mapped_position) != 0U)
    {
        if ((command_context.valid == 0U) || (mapped_position != command_context.latest_position))
        {
            command_context.latest_position = mapped_position;
            command_context.valid = 1U;
            command_context.state = COMMAND_STATE_VALID;
        }
        else
        {
            command_context.state = COMMAND_STATE_WAIT_RX;
        }
    }
    else
    {
        command_context.state = COMMAND_STATE_INVALID;
        command_context.valid = 0U;
    }
}

uint8_t CommandParser_PollUart(void)
{
    uint8_t rx_byte = 0U;
    uint8_t received = 0U;

    if (HAL_UART_Receive(&huart2, &rx_byte, 1U, 0U) == HAL_OK)
    {
        CommandParser_ProcessRxByte(rx_byte);
        received = command_context.valid;
    }

    return received;
}

uint8_t CommandParser_GetLatestCommand(uint8_t * position)
{
    uint8_t valid = 0U;

    if (position != (uint8_t *)0)
    {
        if (command_context.valid != 0U)
        {
            *position = command_context.latest_position;
            valid = 1U;
            command_context.valid = 0U;
            command_context.state = COMMAND_STATE_WAIT_RX;
        }
    }

    return valid;
}
