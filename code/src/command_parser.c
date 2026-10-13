/**
 * @file command_parser.c
 * @brief Command Parser implementation.
 *
 * Software Unit : Command Parser
 * Traces        : SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 * Platform      : STM32F407G-DISC1, STM32 HAL (UART)
 */

#include "command_parser.h"
#include "stm32f4xx_hal.h"

/* ---------- Platform binding ------------------------------------------- */
/* UART handle – defined externally by STM32 HAL / CubeMX generated code   */
extern UART_HandleTypeDef huart2;  /* USART2 on STM32F407-DISC1 (ST-Link VCP) */

/* ---------- Static data (SWE-REQ-009, SWE-REQ-036, SWE-REQ-038) ------- */
static CmdParserData_t cmdData;
static uint8_t         rxByte;     /* Single-byte receive buffer */

/* Allowed position values table (SWE-REQ-027, SWE-REQ-030) */
static const uint8_t allowedPositions[CMD_NUM_POSITIONS] =
{
    CMD_POS_FULLY_CLOSED,
    CMD_POS_25_PERCENT,
    CMD_POS_50_PERCENT,
    CMD_POS_75_PERCENT,
    CMD_POS_FULLY_OPEN
};

/* ---------- Private helpers -------------------------------------------- */

/**
 * @brief Check if a byte is a valid position command.
 * Traces: SWE-REQ-002
 */
static uint8_t IsValidPosition(uint8_t byte)
{
    uint8_t i;
    for (i = 0U; i < CMD_NUM_POSITIONS; i++)
    {
        if (byte == allowedPositions[i])
        {
            return 1U;
        }
    }
    return 0U;
}

/* ---------- Public API ------------------------------------------------- */

void CommandParser_Init(void)
{
    cmdData.position = 0U;
    cmdData.valid    = 0U;
    cmdData.state    = CMD_STATE_WAIT_RX;
    rxByte           = 0U;
}

void CommandParser_Process(void)
{
    HAL_StatusTypeDef status;

    /* Non-blocking single-byte receive (SWE-REQ-022) */
    status = HAL_UART_Receive(&huart2, &rxByte, 1U, 0U);

    if (status == HAL_OK)
    {
        if (IsValidPosition(rxByte) != 0U)
        {
            /* Latest-wins: overwrite previous command (SWE-REQ-003) */
            cmdData.position = rxByte;
            cmdData.valid    = 1U;
            cmdData.state    = CMD_STATE_VALID;
        }
        else
        {
            /* Invalid / unsupported – ignore, no acknowledge (SWE-REQ-002) */
            cmdData.state = CMD_STATE_INVALID;
        }
    }
    /* If HAL_TIMEOUT or HAL_BUSY: no byte available – remain in WAIT_RX */

    if (cmdData.state == CMD_STATE_INVALID)
    {
        /* Flush: return to wait state (LLD transition INVALID->WAIT_RX) */
        cmdData.state = CMD_STATE_WAIT_RX;
    }
}

uint8_t CommandParser_GetLatestCommand(uint8_t *pPosition)
{
    if ((pPosition != ((void *)0)) && (cmdData.valid == 1U))
    {
        *pPosition    = cmdData.position;
        cmdData.valid = 0U;   /* Consume the command */
        return 1U;
    }
    return 0U;
}
