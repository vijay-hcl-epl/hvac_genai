/**
 * @file command_parser.c
 * @brief Command Parser implementation.
 *
 * Software Unit: Command Parser
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 * No dynamic allocation (SWE-REQ-036).  All state is static.
 */

#include "command_parser.h"

/* ---- Static (module-level) data  [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] ---- */

/** Latest validated position command (1..CMD_NUM_POSITIONS). */
static uint8_t s_latest_position = 0U;

/** True when a new, unconsumed valid command is available. */
static bool    s_valid_flag      = false;

/* ---- Allowed position table (static mapping) [SWE-REQ-027, SWE-REQ-030] ---- */

/**
 * Lookup table of allowed command byte values.
 * Design assumption: bytes 0x01..0x05 represent positions 1..5.
 * Table stored in flash (const) – adjust if encoding changes.
 */
static const uint8_t s_allowed_positions[CMD_NUM_POSITIONS] =
{
    1U, 2U, 3U, 4U, 5U
};

/* ---- Private helpers ---- */

/**
 * @brief Check whether a byte is an allowed position command.
 * @return The position (1-based) or 0 if invalid.
 */
static uint8_t validate_byte(uint8_t byte)
{
    uint8_t i;
    for (i = 0U; i < CMD_NUM_POSITIONS; i++)
    {
        if (byte == s_allowed_positions[i])
        {
            return byte;  /* valid – value equals position number */
        }
    }
    return 0U;  /* invalid */
}

/* ---- Public API ---- */

void command_parser_init(void)
{
    s_latest_position = 0U;
    s_valid_flag      = false;
}

/*
 * SWE-REQ-001 : process single-byte UART command
 * SWE-REQ-002 : ignore invalid commands
 * SWE-REQ-003 : latest command wins (overwrites)
 * SWE-REQ-022 : constantly monitor UART input
 */
void command_parser_process_byte(uint8_t rx_byte)
{
    uint8_t pos = validate_byte(rx_byte);

    if (pos == 0U)
    {
        /* Invalid / unsupported – silently ignore [SWE-REQ-002] */
        return;
    }

    /* Store latest valid command (latest wins) [SWE-REQ-003] */
    s_latest_position = pos;
    s_valid_flag      = true;
}

bool command_parser_get_latest(uint8_t *position)
{
    if ((position == ((void *)0)) || (!s_valid_flag))
    {
        return false;
    }

    *position    = s_latest_position;
    s_valid_flag = false;  /* consumed */
    return true;
}
