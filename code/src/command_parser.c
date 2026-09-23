/**
 * @file    command_parser.c
 * @brief   Command Parser software unit – implementation.
 *
 * Traceability:
 *   SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022,
 *   SWE-REQ-036, SWE-REQ-038, SWE-REQ-041.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 */

/* ---- Includes ------------------------------------------------------- */
#include "command_parser.h"
#include "stm32f4xx_hal.h"

/* ---- Private Constants ---------------------------------------------- */

/** @brief UART receive timeout (ms) – non-blocking poll.
 *  Configurable responsiveness parameter (SWE-REQ-035). */
#define CMD_UART_TIMEOUT_MS   (1U)

/* ---- Extern HAL Handle (configured in system_init) ------------------ */
extern UART_HandleTypeDef huart2;

/* ---- Static Data (SWE-REQ-009, SWE-REQ-036) ------------------------ */

/** @brief Allowed command byte table.
 *  Position 0 = 0x30 ('0'), 1 = 0x31 ('1'), … 4 = 0x34 ('4').
 *  Statically initialised (SWE-REQ-030, SWE-REQ-038). */
const uint8_t CMD_ALLOWED_TABLE[CMD_NUM_POSITIONS] =
{
    0x30U, /* Position 0 – CLOSED      */
    0x31U, /* Position 1 – 25 %        */
    0x32U, /* Position 2 – 50 %        */
    0x33U, /* Position 3 – 75 %        */
    0x34U  /* Position 4 – FULLY OPEN  */
};

/** @brief Internal command data (single-slot, latest wins). */
static CommandData_t s_cmdData;

/* ---- Private Helpers ------------------------------------------------ */

/**
 * @brief  Check if a byte matches any entry in the allowed table.
 * @param  byte  Received UART byte.
 * @param[out] pPos  Matched position index (0..4).
 * @return true if valid.
 *         [SWE-REQ-001, SWE-REQ-002]
 */
static bool CMD_IsValidByte(uint8_t byte, uint8_t *pPos)
{
    uint8_t i;
    for (i = 0U; i < CMD_NUM_POSITIONS; i++)
    {
        if (byte == CMD_ALLOWED_TABLE[i])
        {
            *pPos = i;
            return true;
        }
    }
    return false;
}

/* ---- Public API Implementation -------------------------------------- */

/* [SWE-REQ-020] */
void CommandParser_Init(void)
{
    s_cmdData.position = 0U;
    s_cmdData.valid    = false;
    s_cmdData.state    = CMD_STATE_WAIT_RX;
}

/* [SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022] */
void CommandParser_Process(void)
{
    uint8_t rxByte = 0U;
    HAL_StatusTypeDef status;
    uint8_t mappedPos = 0U;

    /* Attempt a non-blocking single-byte UART receive. */
    status = HAL_UART_Receive(&huart2, &rxByte, 1U, CMD_UART_TIMEOUT_MS);

    if (status == HAL_OK)
    {
        /* Byte received – validate against allowed table. */
        if (CMD_IsValidByte(rxByte, &mappedPos))
        {
            /* Valid command – store (latest wins, SWE-REQ-003). */
            s_cmdData.position = mappedPos;
            s_cmdData.valid    = true;
            s_cmdData.state    = CMD_STATE_VALID;
        }
        else
        {
            /* Invalid / unsupported – ignore (SWE-REQ-002). */
            s_cmdData.state = CMD_STATE_INVALID;
        }
    }
    else
    {
        /* No data or error – remain in WAIT_RX. */
        if (s_cmdData.state == CMD_STATE_INVALID)
        {
            /* Flush: return to waiting (LLD transition INVALID→WAIT_RX). */
            s_cmdData.state = CMD_STATE_WAIT_RX;
        }
    }
}

/* [SWE-REQ-001, SWE-REQ-003] */
bool CommandParser_GetLatestCommand(uint8_t *pPosition)
{
    if ((pPosition != (void *)0) && (s_cmdData.valid == true))
    {
        *pPosition = s_cmdData.position;
        return true;
    }
    return false;
}

/* [SWE-REQ-003] */
void CommandParser_ConsumeCommand(void)
{
    s_cmdData.valid = false;
    s_cmdData.state = CMD_STATE_WAIT_RX;
}
