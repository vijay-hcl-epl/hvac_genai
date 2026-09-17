#include "Command Parser.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

#define COMMAND_PARSER_ALLOWED_COUNT (4U)

typedef enum
{
    COMMAND_PARSER_STATE_INIT = 0,
    COMMAND_PARSER_STATE_WAIT_RX,
    COMMAND_PARSER_STATE_VALID,
    COMMAND_PARSER_STATE_INVALID
} Command_Parser_StateType;

typedef struct
{
    uint8_t command_byte;
    uint8_t position;
} Command_Parser_MapType;

static const Command_Parser_MapType Command_Parser_AllowedMap[COMMAND_PARSER_ALLOWED_COUNT] =
{
    { (uint8_t)'0', 0U },
    { (uint8_t)'1', 1U },
    { (uint8_t)'2', 2U },
    { (uint8_t)'3', 3U }
};

static Command_Parser_StateType Command_Parser_State = COMMAND_PARSER_STATE_INIT;
static uint8_t Command_Parser_LatestPosition = 0U;
static bool Command_Parser_Valid = false;

void Command_Parser_Init(void)
{
    Command_Parser_State = COMMAND_PARSER_STATE_WAIT_RX;
    Command_Parser_LatestPosition = 0U;
    Command_Parser_Valid = false;
}

void Command_Parser_Update(void)
{
    uint8_t rx_byte = 0U;
    uint8_t index = 0U;
    bool matched = false;

    if (Command_Parser_State == COMMAND_PARSER_STATE_INIT)
    {
        Command_Parser_Init();
    }

    if (HAL_UART_Receive(&huart2, &rx_byte, 1U, 0U) == HAL_OK)
    {
        for (index = 0U; index < COMMAND_PARSER_ALLOWED_COUNT; index++)
        {
            if (rx_byte == Command_Parser_AllowedMap[index].command_byte)
            {
                if ((Command_Parser_Valid == false) ||
                    (Command_Parser_LatestPosition != Command_Parser_AllowedMap[index].position))
                {
                    Command_Parser_LatestPosition = Command_Parser_AllowedMap[index].position;
                    Command_Parser_Valid = true;
                    Command_Parser_State = COMMAND_PARSER_STATE_VALID;
                }
                matched = true;
                break;
            }
        }

        if (matched == false)
        {
            Command_Parser_Valid = false;
            Command_Parser_State = COMMAND_PARSER_STATE_INVALID;
        }
    }
    else if (Command_Parser_State == COMMAND_PARSER_STATE_INVALID)
    {
        Command_Parser_State = COMMAND_PARSER_STATE_WAIT_RX;
    }
    else
    {
        /* No new UART byte available; retain latest valid command state. */
    }
}

bool Command_Parser_GetLatestCommand(uint8_t * position)
{
    bool ret = false;

    if ((position != (void *)0) && (Command_Parser_Valid == true))
    {
        *position = Command_Parser_LatestPosition;
        ret = true;
    }

    return ret;
}

void Command_Parser_Clear(void)
{
    Command_Parser_Valid = false;
    Command_Parser_State = COMMAND_PARSER_STATE_WAIT_RX;
}
