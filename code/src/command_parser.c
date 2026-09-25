/**
 * @file command_parser.c
 * @brief Command Parser implementation – UART byte parsing, validation, latest-wins.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 * Platform: STM32F407G-DISC1 / STM32 HAL / USART2
 */

#include "command_parser.h"
#include "stm32f4xx_hal.h"

/* ---- Private types / data (static, no dynamic allocation) ---- */

/** Allowed position command lookup table [SWE-REQ-027, SWE-REQ-030] */
static const uint8_t allowed_positions[CMD_NUM_POSITIONS] =
{
    CMD_POS_1,
    CMD_POS_2,
    CMD_POS_3,
    CMD_POS_4,
    CMD_POS_5
};

/** Internal state – latest command byte and validity flag */
static uint8_t  s_latest_cmd;
static uint8_t  s_cmd_valid;

/** Single-byte UART receive buffer (static) [SWE-REQ-038] */
static uint8_t  s_uart_rx_byte;

/* Extern UART handle – expected to be defined by STM32CubeMX generated code */
extern UART_HandleTypeDef huart2;

/* ---- Private helpers ---- */

/**
 * @brief Check whether a byte is a supported position command.
 * @param byte  The received byte.
 * @return 1 if valid, 0 otherwise.
 */
static uint8_t is_valid_command(uint8_t byte)
{
    uint8_t i;
    uint8_t result = 0U;

    for (i = 0U; i < CMD_NUM_POSITIONS; i++)
    {
        if (byte == allowed_positions[i])
        {
            result = 1U;
            break;
        }
    }
    return result;
}

/* ---- Public API ---- */

void command_parser_init(void)
{
    s_latest_cmd  = CMD_INVALID;
    s_cmd_valid   = 0U;
    s_uart_rx_byte = 0U;
}

void command_parser_update(void)
{
    HAL_StatusTypeDef status;

    /* Non-blocking single-byte receive [SWE-REQ-022] */
    status = HAL_UART_Receive(&huart2, &s_uart_rx_byte, 1U, 0U);

    if (status == HAL_OK)
    {
        if (is_valid_command(s_uart_rx_byte) != 0U)
        {
            /* Latest wins – overwrite previous [SWE-REQ-003] */
            s_latest_cmd = s_uart_rx_byte;
            s_cmd_valid  = 1U;
        }
        else
        {
            /* Invalid / unsupported command – silently ignore [SWE-REQ-002] */
        }
    }
}

uint8_t command_parser_get_latest(uint8_t *p_position)
{
    uint8_t available = 0U;

    if ((p_position != (void *)0) && (s_cmd_valid != 0U))
    {
        *p_position = s_latest_cmd;
        s_cmd_valid = 0U;       /* Clear after read */
        available   = 1U;
    }
    return available;
}
