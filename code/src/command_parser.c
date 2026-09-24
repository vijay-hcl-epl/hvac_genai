/**
 * @file command_parser.c
 * @brief Command Parser implementation.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 */

#include "command_parser.h"
#include "stm32f4xx_hal.h"

/* ---- Platform configuration ---- */
/* UART handle (defined in main / system_init, linked externally) */
extern UART_HandleTypeDef huart2;

/* ---- Static allowed-position table [SWE-REQ-027, SWE-REQ-030] ---- */
static const uint8_t allowedPositions[CMD_NUM_POSITIONS] =
{
    CMD_POS_1, CMD_POS_2, CMD_POS_3, CMD_POS_4, CMD_POS_5
};

/* ---- Module-level static data (no dynamic alloc) [SWE-REQ-009, SWE-REQ-036] ---- */
static CmdResult_t s_cmdResult;
static uint8_t     s_rxByte;

/* ---- Private helpers ---- */

/**
 * @brief Check if a byte is a valid position command.
 * @param byte  Received byte
 * @return 1 if valid, 0 otherwise
 */
static uint8_t CmdParser_IsValid(uint8_t byte)
{
    uint8_t i;
    uint8_t result = 0U;

    for (i = 0U; i < CMD_NUM_POSITIONS; i++)
    {
        if (byte == allowedPositions[i])
        {
            result = 1U;
            break;
        }
    }
    return result;
}

/* ---- Public API ---- */

void CommandParser_Init(void)
{
    s_cmdResult.position = 0U;
    s_cmdResult.valid    = 0U;
    s_cmdResult.state    = CMD_STATE_WAIT_RX;
    s_rxByte             = 0U;
}

void CommandParser_Process(void)
{
    HAL_StatusTypeDef rxStatus;

    /* Non-blocking receive of 1 byte [SWE-REQ-015, SWE-REQ-022] */
    rxStatus = HAL_UART_Receive(&huart2, &s_rxByte, 1U, 0U);

    if (rxStatus == HAL_OK)
    {
        if (CmdParser_IsValid(s_rxByte) != 0U)
        {
            /* Valid command – store (latest wins) [SWE-REQ-001, SWE-REQ-003] */
            s_cmdResult.position = s_rxByte;
            s_cmdResult.valid    = 1U;
            s_cmdResult.state    = CMD_STATE_VALID;
        }
        else
        {
            /* Invalid / unsupported – ignore [SWE-REQ-002] */
            s_cmdResult.state = CMD_STATE_INVALID;
            /* Do NOT clear a previously valid command */
        }
    }
    /* If no data available (HAL_TIMEOUT), do nothing – keep previous state */
}

CmdResult_t CommandParser_GetLatestCommand(void)
{
    return s_cmdResult;
}

void CommandParser_ClearCommand(void)
{
    s_cmdResult.valid = 0U;
    s_cmdResult.state = CMD_STATE_WAIT_RX;
}
