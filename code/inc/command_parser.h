/**
 * @file command_parser.h
 * @brief Command Parser – UART byte parsing and validation for flap position commands.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

/** Number of supported flap positions (positions 0..4) */
#define CMD_NUM_POSITIONS  (5U)

/** Position value representing "no valid command received" */
#define CMD_POSITION_NONE  (0xFFU)

/**
 * @brief Command data returned to caller.
 *
 * Traces: SWE-REQ-001, SWE-REQ-003
 */
typedef struct
{
    uint8_t position;   /**< Commanded flap position (0..CMD_NUM_POSITIONS-1) or CMD_POSITION_NONE */
    uint8_t valid;      /**< 1 = valid command available, 0 = no valid command */
} CommandData_t;

/**
 * @brief Initialise the command parser internal state.
 *
 * Traces: SWE-REQ-020
 */
void CommandParser_Init(void);

/**
 * @brief Process a single incoming UART byte.
 *
 * Checks the byte against the allowed position table.
 * If valid, stores as latest command (latest-wins, SWE-REQ-003).
 * If invalid, ignores silently (SWE-REQ-002).
 *
 * @param[in] rx_byte  Byte received from UART.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 */
void CommandParser_ProcessByte(uint8_t rx_byte);

/**
 * @brief Retrieve the latest validated command and clear it.
 *
 * @return CommandData_t  Latest command data with valid flag.
 *
 * Traces: SWE-REQ-001, SWE-REQ-003
 */
CommandData_t CommandParser_GetLatestCommand(void);

#endif /* COMMAND_PARSER_H */
