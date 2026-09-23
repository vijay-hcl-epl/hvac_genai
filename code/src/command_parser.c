/**
 * @file command_parser.c
 * @brief Command Parser Software Unit – Implementation
 *
 * Traceability:
 *   SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1, STM32 HAL (USART2), bare-metal
 */

#include "command_parser.h"
#include "stm32f4xx_hal.h"

/* ---------- Hardware binding (env-setup: UART) ---------- */

/**
 * @brief UART handle – assumed USART2 for USB-to-UART on STM32F407-DISC1.
 *        Declared extern; created by the peripheral-init code in system_init.
 *        [SWE-REQ-015, SWE-REQ-019]
 */
extern UART_HandleTypeDef huart2;

/* ---------- Static module data (no dynamic allocation) ---------- */
/* [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] */

/** Internal state of the command parser state machine */
static CommandParserState_t s_state = CMD_STATE_INIT;

/** Latest validated command result */
static CommandResult_t s_latestCmd = { 0U, false };

/** One-byte receive buffer for HAL UART [SWE-REQ-038] */
static uint8_t s_rxByte = 0U;

/* ---------- Private helpers ---------- */

/**
 * @brief Check whether a received byte represents a valid position command.
 * @param byte  The received byte.
 * @return true if byte is within [CMD_PARSER_POS_MIN .. CMD_PARSER_POS_MAX].
 *         [SWE-REQ-001, SWE-REQ-002]
 */
static bool IsValidPosition(uint8_t byte)
{
    return ((byte >= CMD_PARSER_POS_MIN) && (byte <= CMD_PARSER_POS_MAX));
}

/* ---------- Public API ---------- */

/**
 * @brief Initialise the Command Parser unit.
 *        [SWE-REQ-020]
 */
void CommandParser_Init(void)
{
    s_state            = CMD_STATE_WAIT_RX;
    s_latestCmd.position = 0U;
    s_latestCmd.valid    = false;
    s_rxByte             = 0U;
}

/**
 * @brief Process any pending UART received byte.
 *
 * Uses HAL_UART_Receive in non-blocking (timeout = 0) fashion to
 * check for a single byte.  If a byte arrives it is validated against
 * the allowed position table.
 *
 * [SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-022]
 */
void CommandParser_Process(void)
{
    HAL_StatusTypeDef rxStatus;

    /* Attempt to read one byte with zero timeout (non-blocking poll).
     * [SWE-REQ-015, SWE-REQ-022] */
    rxStatus = HAL_UART_Receive(&huart2, &s_rxByte, 1U, 0U);

    if (rxStatus == HAL_OK)
    {
        if (IsValidPosition(s_rxByte))
        {
            /* Valid command – store (latest wins) [SWE-REQ-003] */
            s_latestCmd.position = s_rxByte;
            s_latestCmd.valid    = true;
            s_state              = CMD_STATE_VALID;
        }
        else
        {
            /* Invalid / unsupported command – ignore [SWE-REQ-002] */
            s_state = CMD_STATE_INVALID;
            /* Transition back to WAIT_RX on next call (flush) */
        }
    }
    else
    {
        /* No data available or error – remain in WAIT_RX */
        if (s_state == CMD_STATE_INVALID)
        {
            /* Flush transition: INVALID -> WAIT_RX */
            s_state = CMD_STATE_WAIT_RX;
        }
    }
}

/**
 * @brief Retrieve the latest validated command.
 *        [SWE-REQ-001, SWE-REQ-003]
 */
CommandResult_t CommandParser_GetLatestCommand(void)
{
    return s_latestCmd;
}

/**
 * @brief Clear the current valid command (consumed by control logic).
 *        [SWE-REQ-003]
 */
void CommandParser_ClearCommand(void)
{
    s_latestCmd.valid = false;
    s_state = CMD_STATE_WAIT_RX;
}
