/**
 * @file command_parser.c
 * @brief Command Parser implementation.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "command_parser.h"

/* ---------- Static (module-scope) data – no dynamic allocation (SWE-REQ-036, SWE-REQ-038) ---------- */

/** Allowed position values lookup table (SWE-REQ-027, SWE-REQ-030) */
static const uint8_t g_allowed_positions[CMD_NUM_POSITIONS] =
{
    CMD_POS_CLOSED,
    CMD_POS_25,
    CMD_POS_50,
    CMD_POS_75,
    CMD_POS_OPEN
};

/** Latest validated command byte */
static uint8_t g_latest_command = CMD_INVALID;

/** Validity flag: 1 = new unread command available, 0 = consumed / none */
static uint8_t g_command_valid  = 0U;

/* ---------- Private helpers ---------- */

/**
 * @brief Check whether a byte is in the allowed position table.
 * @param byte  Candidate command byte.
 * @return 1 if valid, 0 otherwise.
 */
static uint8_t IsPositionValid(uint8_t byte)
{
    uint8_t i;
    uint8_t result = 0U;

    for (i = 0U; i < CMD_NUM_POSITIONS; i++)
    {
        if (g_allowed_positions[i] == byte)
        {
            result = 1U;
            break;
        }
    }
    return result;
}

/* ---------- Public API ---------- */

void CommandParser_Init(void)
{
    g_latest_command = CMD_INVALID;
    g_command_valid  = 0U;
}

void CommandParser_ProcessByte(uint8_t rx_byte)
{
    /* SWE-REQ-002: ignore invalid commands */
    if (IsPositionValid(rx_byte) == 0U)
    {
        return; /* silently discard */
    }

    /* SWE-REQ-003: latest wins – overwrite regardless of previous */
    g_latest_command = rx_byte;
    g_command_valid  = 1U;
}

void CommandParser_GetLatestCommand(uint8_t *p_position, uint8_t *p_valid)
{
    if ((p_position != (void *)0) && (p_valid != (void *)0))
    {
        *p_position = g_latest_command;
        *p_valid    = g_command_valid;

        /* Clear after read so the command is consumed once */
        g_command_valid = 0U;
    }
}
