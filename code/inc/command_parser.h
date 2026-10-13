/**
 * @file command_parser.h
 * @brief Command Parser – UART byte parsing and validation for flap position commands.
 *
 * Software Unit: Command Parser
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 *
 * ASSUMPTIONS (not verified on hardware):
 *   - UART handle (huart2) is initialised by system_init before use.
 *   - Position command byte values 0x01..0x05 map to FLAP_POS_1..FLAP_POS_5.
 *     Actual byte encoding is a design assumption; adjust to match the PC tool.
 */
#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/** Number of supported flap positions (design assumption: 5 discrete positions). */
#define CMD_NUM_POSITIONS  5U

/** Allowed single-byte position command values (1-based). */
#define CMD_POS_MIN        1U
#define CMD_POS_MAX        CMD_NUM_POSITIONS

/**
 * @brief Initialise the Command Parser internal state.
 *
 * Clears latest command and validity flag.
 * Called once from system_init().
 * Traces: SWE-REQ-020 (init)
 */
void command_parser_init(void);

/**
 * @brief Process one incoming UART byte.
 *
 * Checks byte against the allowed position table.
 * If valid and different from the previous command, stores as latest command
 * and sets the valid flag.  Invalid / duplicate bytes are silently ignored.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-022
 *
 * @param rx_byte  The byte received from UART.
 */
void command_parser_process_byte(uint8_t rx_byte);

/**
 * @brief Retrieve the latest validated position command.
 *
 * After reading, the valid flag is cleared (consumed).
 *
 * Traces: SWE-REQ-001, SWE-REQ-003, SWE-REQ-015
 *
 * @param[out] position  Pointer to store the commanded position (1..CMD_NUM_POSITIONS).
 * @return true if a new valid command was available; false otherwise.
 */
bool command_parser_get_latest(uint8_t *position);

#endif /* COMMAND_PARSER_H */
