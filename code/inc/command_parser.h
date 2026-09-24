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

/** Number of supported flap positions (0..4 mapped to CLOSED, 25%, 50%, 75%, OPEN) */
#define CMD_NUM_POSITIONS  (5U)

/** Position command identifiers sent over UART */
#define CMD_POS_CLOSED     (0x00U)
#define CMD_POS_25         (0x01U)
#define CMD_POS_50         (0x02U)
#define CMD_POS_75         (0x03U)
#define CMD_POS_OPEN       (0x04U)

/** Invalid / no-command sentinel */
#define CMD_INVALID        (0xFFU)

/**
 * @brief Initialise the command parser internal state.
 *
 * Clears stored command and validity flag.
 * Called once from system_init().
 *
 * Traces: SWE-REQ-020
 */
void CommandParser_Init(void);

/**
 * @brief Process one incoming UART byte.
 *
 * Checks the byte against the allowed position table.
 * - If valid and different from the stored command, updates stored command and sets valid flag.
 * - If invalid or duplicate, the byte is silently discarded (SWE-REQ-002).
 * Latest-wins policy: only the most recent valid command is kept (SWE-REQ-003).
 *
 * @param rx_byte  Raw byte received from UART.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015
 */
void CommandParser_ProcessByte(uint8_t rx_byte);

/**
 * @brief Retrieve the latest validated command.
 *
 * @param[out] p_position  Pointer to store the position value (CMD_POS_xxx).
 * @param[out] p_valid     Pointer to store validity flag (1 = valid, 0 = no new command).
 *
 * After reading, the valid flag is cleared so the same command is not re-consumed.
 *
 * Traces: SWE-REQ-001, SWE-REQ-022
 */
void CommandParser_GetLatestCommand(uint8_t *p_position, uint8_t *p_valid);

#endif /* COMMAND_PARSER_H */
