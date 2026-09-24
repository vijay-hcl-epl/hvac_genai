/**
 * @file command_parser.h
 * @brief Command Parser – UART command parsing and validation.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Parses single-byte UART commands, validates against the allowed position
 * table, and provides the latest valid command to the Flap Control Logic.
 * Only one queued command at a time (latest wins).
 * No dynamic memory allocation. All data is statically allocated.
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

/** Number of valid flap positions supported */
#define CMD_NUM_POSITIONS  (5U)

/** Position command byte definitions (sent from PC via UART) */
#define CMD_POS_1  (0x01U)
#define CMD_POS_2  (0x02U)
#define CMD_POS_3  (0x03U)
#define CMD_POS_4  (0x04U)
#define CMD_POS_5  (0x05U)

/** Command parser states */
typedef enum
{
    CMD_STATE_INIT    = 0U,
    CMD_STATE_WAIT_RX = 1U,
    CMD_STATE_VALID   = 2U,
    CMD_STATE_INVALID = 3U
} CmdParserState_t;

/** Command result structure */
typedef struct
{
    uint8_t          position;   /**< Parsed target position (1..5) */
    uint8_t          valid;      /**< 1 = valid command available, 0 = none */
    CmdParserState_t state;      /**< Current parser state */
} CmdResult_t;

/**
 * @brief Initialise the command parser module.
 *        Sets state to CMD_STATE_WAIT_RX, clears stored command.
 *        [SWE-REQ-020]
 */
void CommandParser_Init(void);

/**
 * @brief Process incoming UART data (call cyclically or on RX event).
 *        Reads one byte from UART; validates against the allowed table.
 *        On valid: stores command, sets valid flag.
 *        On invalid: ignores, clears valid flag.
 *        [SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-022]
 */
void CommandParser_Process(void);

/**
 * @brief Retrieve the latest parsed command.
 * @return CmdResult_t with position and validity flag.
 *         [SWE-REQ-001, SWE-REQ-003]
 */
CmdResult_t CommandParser_GetLatestCommand(void);

/**
 * @brief Clear / consume the latest command after it has been processed.
 *        Resets valid flag to 0.
 */
void CommandParser_ClearCommand(void);

#endif /* COMMAND_PARSER_H */
