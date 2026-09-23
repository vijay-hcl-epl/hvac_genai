/**
 * @file command_parser.h
 * @brief Command Parser – UART byte parsing and validation for flap position commands.
 *
 * Software Unit: Command Parser
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Supported flap position commands (single-byte UART values).
 *        Five discrete positions mapped to command bytes 0x01..0x05.
 */
#define CMD_POS_1       ((uint8_t)0x01U)
#define CMD_POS_2       ((uint8_t)0x02U)
#define CMD_POS_3       ((uint8_t)0x03U)
#define CMD_POS_4       ((uint8_t)0x04U)
#define CMD_POS_5       ((uint8_t)0x05U)

#define CMD_NUM_POSITIONS ((uint8_t)5U)

/** Command Parser states per LLD state machine */
typedef enum
{
    CMDPARSE_STATE_INIT    = 0U,
    CMDPARSE_STATE_WAIT_RX = 1U,
    CMDPARSE_STATE_VALID   = 2U,
    CMDPARSE_STATE_INVALID = 3U
} CommandParserState_t;

/** Command result structure returned by get_latest_command() */
typedef struct
{
    uint8_t position;   /**< Last validated position command (1..5) */
    bool    valid;      /**< true if a valid command is pending    */
} CommandResult_t;

/**
 * @brief Initialise the Command Parser unit.
 *        Sets state to WAIT_RX, clears stored command.
 *        [SWE-REQ-020]
 */
void CommandParser_Init(void);

/**
 * @brief Process incoming UART data.
 *        Call cyclically or on UART RX event.
 *        Reads one byte via HAL UART, validates against allowed table.
 *        Latest command wins (SWE-REQ-003).
 *        [SWE-REQ-001, SWE-REQ-002, SWE-REQ-022]
 */
void CommandParser_Process(void);

/**
 * @brief Retrieve the latest validated command.
 * @return CommandResult_t  position + valid flag.
 *         After read, the valid flag is cleared (consumed).
 *         [SWE-REQ-001, SWE-REQ-003]
 */
CommandResult_t CommandParser_GetLatestCommand(void);

#endif /* COMMAND_PARSER_H */
