/**
 * @file command_parser.c
 * @brief Command Parser implementation – UART byte reception, validation, storage.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "command_parser.h"
#include "stm32f4xx_hal.h"

/* ---- Private types ---------------------------------------------------- */

/** Internal state of the command parser (LLD state machine). */
typedef enum
{
    CMDP_STATE_INIT    = 0U,
    CMDP_STATE_WAIT_RX = 1U,
    CMDP_STATE_VALID   = 2U,
    CMDP_STATE_INVALID = 3U
} CmdParserState_t;

/** Static command data (no dynamic allocation – SWE-REQ-036). */
typedef struct
{
    CmdParserState_t state;
    uint8_t          latest_position;
    bool             valid;
} CmdParserData_t;

/* ---- Private data ----------------------------------------------------- */

/** Allowed position lookup table (SWE-REQ-027, SWE-REQ-030). */
static const uint8_t s_allowed_positions[CMD_NUM_POSITIONS] =
{
    CMD_POS_FULLY_CLOSED,
    CMD_POS_QUARTER_OPEN,
    CMD_POS_HALF_OPEN,
    CMD_POS_THREE_QTR,
    CMD_POS_FULLY_OPEN
};

static CmdParserData_t s_cmd_data;

/** Single-byte UART RX buffer (static – SWE-REQ-038). */
static uint8_t s_rx_byte;

/* ---- Extern HAL handle (defined in system_init.c) --------------------- */
extern UART_HandleTypeDef huart2;

/* ---- Private helpers -------------------------------------------------- */

/**
 * @brief Check whether a byte matches any allowed position.
 * @param byte  The received UART byte.
 * @return true if byte is a valid position command.
 */
static bool CmdParser_IsValid(uint8_t byte)
{
    bool result = false;
    uint8_t idx;
    for (idx = 0U; idx < CMD_NUM_POSITIONS; idx++)
    {
        if (byte == s_allowed_positions[idx])
        {
            result = true;
            break;
        }
    }
    return result;
}

/* ---- Public API ------------------------------------------------------- */

void CommandParser_Init(void)
{
    s_cmd_data.state           = CMDP_STATE_WAIT_RX;
    s_cmd_data.latest_position = CMD_POS_NONE;
    s_cmd_data.valid           = false;
    s_rx_byte                  = 0U;
}

void CommandParser_Process(void)
{
    HAL_StatusTypeDef status;

    /* Non-blocking single-byte receive (SWE-REQ-022). */
    status = HAL_UART_Receive(&huart2, &s_rx_byte, 1U, 0U);

    if (status == HAL_OK)
    {
        if (CmdParser_IsValid(s_rx_byte))
        {
            /* Latest wins – overwrite previous (SWE-REQ-003). */
            s_cmd_data.latest_position = s_rx_byte;
            s_cmd_data.valid           = true;
            s_cmd_data.state           = CMDP_STATE_VALID;
        }
        else
        {
            /* Invalid / unsupported – silently discard (SWE-REQ-002). */
            s_cmd_data.state = CMDP_STATE_INVALID;
        }
    }
    /* If no byte received, remain in WAIT_RX – no action. */
}

void CommandParser_GetLatestCommand(uint8_t *p_position, bool *p_valid)
{
    if ((p_position != (void *)0) && (p_valid != (void *)0))
    {
        *p_position = s_cmd_data.latest_position;
        *p_valid    = s_cmd_data.valid;
    }
}

void CommandParser_ClearCommand(void)
{
    s_cmd_data.valid           = false;
    s_cmd_data.latest_position = CMD_POS_NONE;
    s_cmd_data.state           = CMDP_STATE_WAIT_RX;
}
