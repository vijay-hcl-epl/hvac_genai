#include "Command Parser.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

#define COMMAND_TABLE_SIZE            (4U)
#define COMMAND_VALID                 (1U)
#define COMMAND_INVALID               (0U)

typedef struct
{
    uint8_t rx_byte;
    uint8_t position;
    uint8_t valid;
} Command_Parser_State_t;

static Command_Parser_State_t command_state;
static const uint8_t command_bytes[COMMAND_TABLE_SIZE] = { (uint8_t)'0', (uint8_t)'1', (uint8_t)'2', (uint8_t)'3' };
static const uint8_t command_positions[COMMAND_TABLE_SIZE] = { 0U, 1U, 2U, 3U };

void Command_Parser_Init(void)
{
    command_state.rx_byte = 0U;
    command_state.position = 0U;
    command_state.valid = COMMAND_INVALID;
}

void Command_Parser_Update(void)
{
    uint8_t byte_value = 0U;
    uint8_t index = 0U;
    uint8_t found = COMMAND_INVALID;

    if (HAL_UART_Receive(&huart2, &byte_value, 1U, 0U) == HAL_OK)
    {
        for (index = 0U; index < COMMAND_TABLE_SIZE; index++)
        {
            if (byte_value == command_bytes[index])
            {
                command_state.rx_byte = byte_value;
                command_state.position = command_positions[index];
                command_state.valid = COMMAND_VALID;
                found = COMMAND_VALID;
                break;
            }
        }

        if (found == COMMAND_INVALID)
        {
            command_state.rx_byte = byte_value;
            command_state.valid = COMMAND_INVALID;
        }
    }
}

void Command_Parser_Get_Latest_Command(uint8_t * position, uint8_t * valid)
{
    if ((position != (void *)0) && (valid != (void *)0))
    {
        *position = command_state.position;
        *valid = command_state.valid;
    }
}

void Command_Parser_Clear_Command(void)
{
    command_state.valid = COMMAND_INVALID;
}
