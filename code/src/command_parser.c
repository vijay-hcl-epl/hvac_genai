/**
 * @file command_parser.c
 * @brief Command Parser implementation.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "command_parser.h"

/* ---- Static allowed-position table (SWE-REQ-027, SWE-REQ-030) ---- */

/**
 * @brief Allowed single-byte UART command values mapped to positions.
 *
 * Index = position, Value = expected UART byte ('0'..'4').
 * Traces: SWE-REQ-001, SWE-REQ-038
 */
static const uint8_t g_allowed_cmds[CMD_NUM_POSITIONS] =
{
    (uint8_t)'0',  /* Position 0 */
    (uint8_t)'1',  /* Position 1 */
    (uint8_t)'2',  /* Position 2 */
    (uint8_t)'3',  /* Position 3 */
    (uint8_t)'4'   /* Position 4 */
};

/* ---- Internal static state (SWE-REQ-009, SWE-REQ-036) ---- */

/** Latest command storage – single slot, latest-wins (SWE-REQ-003) */
static CommandData_t g_latest_cmd;

/* ================================================================== */

void CommandParser_Init(void)
{
    g_latest_cmd.position = CMD_POSITION_NONE;
    g_latest_cmd.valid    = 0U;
}

/* ------------------------------------------------------------------ */

void CommandParser_ProcessByte(uint8_t rx_byte)
{
    uint8_t idx;
    uint8_t found = 0U;

    /* Look up received byte in allowed table (SWE-REQ-001) */
    for (idx = 0U; idx < CMD_NUM_POSITIONS; idx++)
    {
        if (rx_byte == g_allowed_cmds[idx])
        {
            found = 1U;
            break;
        }
    }

    if (found != 0U)
    {
        /* Valid command – store as latest (SWE-REQ-003) */
        g_latest_cmd.position = idx;
        g_latest_cmd.valid    = 1U;
    }
    else
    {
        /* Invalid / unsupported – ignore silently (SWE-REQ-002) */
        /* No action */
    }
}

/* ------------------------------------------------------------------ */

CommandData_t CommandParser_GetLatestCommand(void)
{
    CommandData_t cmd = g_latest_cmd;

    /* Clear after read (consume command) */
    g_latest_cmd.valid = 0U;

    return cmd;
}
