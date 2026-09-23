/**
 * @file command_parser.h
 * @brief Command Parser Software Unit – Header
 *
 * Parses incoming UART bytes, validates commands against allowed
 * flap-position table, and provides the latest valid command.
 *
 * Traceability:
 *   SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Number of supported flap positions.
 *        Positions encoded as single-byte UART commands: 0x01..0x05
 *        [SWE-REQ-001, SWE-REQ-027, SWE-REQ-038]
 */
#define CMD_PARSER_NUM_POSITIONS  (5U)

/** Minimum valid position command byte [SWE-REQ-001] */
#define CMD_PARSER_POS_MIN        (1U)

/** Maximum valid position command byte [SWE-REQ-001] */
#define CMD_PARSER_POS_MAX        (CMD_PARSER_NUM_POSITIONS)

/**
 * @brief Command Parser states per LLD state machine.
 *        {INIT, WAIT_RX, VALID, INVALID}
 */
typedef enum
{
    CMD_STATE_INIT    = 0U,
    CMD_STATE_WAIT_RX = 1U,
    CMD_STATE_VALID   = 2U,
    CMD_STATE_INVALID = 3U
} CommandParserState_t;

/**
 * @brief Result structure returned by get_latest_command().
 *        [SWE-REQ-001, SWE-REQ-003]
 */
typedef struct
{
    uint8_t position;   /**< Latest commanded position (1..NUM_POSITIONS) */
    bool    valid;      /**< true if a valid command has been received    */
} CommandResult_t;

/**
 * @brief Initialise the Command Parser unit.
 *        Must be called once at startup before any other API.
 *        [SWE-REQ-020]
 */
void CommandParser_Init(void);

/**
 * @brief Process any pending UART received byte.
 *        Call cyclically from the main dispatcher.
 *        [SWE-REQ-022, SWE-REQ-001, SWE-REQ-002, SWE-REQ-003]
 */
void CommandParser_Process(void);

/**
 * @brief Retrieve the latest validated command.
 * @return CommandResult_t  position + valid flag
 *         [SWE-REQ-001, SWE-REQ-003]
 */
CommandResult_t CommandParser_GetLatestCommand(void);

/**
 * @brief Clear the current valid command (consumed by control logic).
 *        [SWE-REQ-003]
 */
void CommandParser_ClearCommand(void);

#endif /* COMMAND_PARSER_H */
