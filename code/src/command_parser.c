/**
 * @file command_parser.c
 * @brief Command Parser implementation – UART byte parsing, validation, command store.
 *
 * Software Unit: Command Parser
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (USART2)
 */

#include "command_parser.h"
#include "stm32f4xx_hal.h"

/* ---------- Static (file-scope) data [SWE-REQ-009, SWE-REQ-036] ---------- */

/** Allowed position command lookup table (static, no dynamic alloc) [SWE-REQ-027, SWE-REQ-038] */
static const uint8_t s_AllowedPositions[CMD_NUM_POSITIONS] =
{
    CMD_POS_1, CMD_POS_2, CMD_POS_3, CMD_POS_4, CMD_POS_5
};

/** Current parser state */
static CommandParserState_t s_State = CMDPARSE_STATE_INIT;

/** Latest validated command storage (latest wins) [SWE-REQ-003] */
static CommandResult_t s_LatestCommand = { 0U, false };

/** Single-byte UART receive buffer (static) [SWE-REQ-038] */
static uint8_t s_RxByte = 0U;

/* External UART handle (defined in system_init.c / STM32CubeMX generated) */
extern UART_HandleTypeDef huart2;

/* ---------- Internal helpers -------------------------------------------- */

/**
 * @brief Check whether a byte is a supported position command.
 * @param byte  The received UART byte.
 * @return true if valid position command, false otherwise.
 *         [SWE-REQ-002]
 */
static bool CommandParser_IsValidPosition(uint8_t byte)
{
    bool result = false;
    uint8_t idx;

    for (idx = 0U; idx < CMD_NUM_POSITIONS; idx++)
    {
        if (byte == s_AllowedPositions[idx])
        {
            result = true;
            break;
        }
    }
    return result;
}

/* ---------- Public API -------------------------------------------------- */

void CommandParser_Init(void)
{
    s_State = CMDPARSE_STATE_WAIT_RX;
    s_LatestCommand.position = 0U;
    s_LatestCommand.valid    = false;
    s_RxByte                 = 0U;
}

void CommandParser_Process(void)
{
    HAL_StatusTypeDef hal_status;

    /* Attempt non-blocking single-byte UART receive [SWE-REQ-015, SWE-REQ-022] */
    hal_status = HAL_UART_Receive(&huart2, &s_RxByte, 1U, 0U);

    if (hal_status == HAL_OK)
    {
        /* Byte received – validate [SWE-REQ-001] */
        if (CommandParser_IsValidPosition(s_RxByte) == true)
        {
            /* Valid command – store (latest wins) [SWE-REQ-003] */
            s_LatestCommand.position = s_RxByte;
            s_LatestCommand.valid    = true;
            s_State                  = CMDPARSE_STATE_VALID;
        }
        else
        {
            /* Invalid / unsupported – ignore, no acknowledge [SWE-REQ-002] */
            s_State = CMDPARSE_STATE_INVALID;
        }
    }
    /* No data available – remain in WAIT_RX (no action) */
}

CommandResult_t CommandParser_GetLatestCommand(void)
{
    CommandResult_t result = s_LatestCommand;

    /* Consume the command after read */
    if (s_LatestCommand.valid == true)
    {
        s_LatestCommand.valid = false;
        s_State               = CMDPARSE_STATE_WAIT_RX;
    }

    return result;
}
