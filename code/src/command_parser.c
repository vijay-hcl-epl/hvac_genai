/**
 * @file command_parser.c
 * @brief Command Parser implementation.
 *
 * Software Unit : Command Parser
 * Traceability  : SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015,
 *                 SWE-REQ-022
 */

#include "command_parser.h"

/* ── Static (module-scope) data – no dynamic allocation (SWE-REQ-036) ── */

/** Allowed position command lookup table (SWE-REQ-027, SWE-REQ-030). */
static const uint8_t s_allowed_cmds[CMD_POSITION_COUNT] =
{
    CMD_POS_0,
    CMD_POS_1,
    CMD_POS_2,
    CMD_POS_3,
    CMD_POS_4
};

/** Latest validated command byte. */
static uint8_t           s_last_position  = 0U;
/** Valid-command flag. */
static uint8_t           s_valid_flag     = 0U;
/** Current parser state. */
static CmdParser_State_t s_state          = CMDPARSER_STATE_INIT;

/* ── Private helpers ───────────────────────────────────────────────────── */

/**
 * @brief Check whether a byte is a supported position command.
 * @param byte  The received byte.
 * @return 1 if valid, 0 otherwise.
 */
static uint8_t IsValidCommand(uint8_t byte)
{
    uint8_t i;
    uint8_t result = 0U;

    for (i = 0U; i < CMD_POSITION_COUNT; i++)
    {
        if (byte == s_allowed_cmds[i])
        {
            result = 1U;
            break;
        }
    }
    return result;
}

/* ── Public API ────────────────────────────────────────────────────────── */

void CmdParser_Init(void)
{
    s_last_position = 0U;
    s_valid_flag    = 0U;
    s_state         = CMDPARSER_STATE_WAIT_RX;
}

void CmdParser_ProcessByte(uint8_t rx_byte)
{
    /* SWE-REQ-001: parse single-byte command.
     * SWE-REQ-002: ignore unsupported commands.
     * SWE-REQ-003: latest wins – overwrite previous.                     */

    if (IsValidCommand(rx_byte) != 0U)
    {
        s_last_position = rx_byte;
        s_valid_flag    = 1U;
        s_state         = CMDPARSER_STATE_VALID;
    }
    else
    {
        /* Invalid / unsupported – ignore, do not update stored command.  */
        s_state = CMDPARSER_STATE_INVALID;
        /* Transition back to WAIT_RX (flush) per LLD state machine.     */
        s_state = CMDPARSER_STATE_WAIT_RX;
    }
}

void CmdParser_GetLatestCommand(CmdParser_Result_t *p_result)
{
    if (p_result != (void *)0)
    {
        p_result->position = s_last_position;
        p_result->valid    = s_valid_flag;
        p_result->state    = s_state;
    }
}

void CmdParser_ClearCommand(void)
{
    s_valid_flag = 0U;
    s_state      = CMDPARSER_STATE_WAIT_RX;
}
