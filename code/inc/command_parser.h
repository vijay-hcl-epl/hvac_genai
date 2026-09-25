/**
 * @file command_parser.h
 * @brief Command Parser – UART byte parsing and flap position command validation.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/** Number of valid flap positions supported. */
#define CMD_NUM_POSITIONS  ((uint8_t)5U)

/** Position identifiers (mapped to UART command bytes). */
#define CMD_POS_FULLY_CLOSED  ((uint8_t)0x01U)
#define CMD_POS_QUARTER_OPEN  ((uint8_t)0x02U)
#define CMD_POS_HALF_OPEN     ((uint8_t)0x03U)
#define CMD_POS_THREE_QTR     ((uint8_t)0x04U)
#define CMD_POS_FULLY_OPEN    ((uint8_t)0x05U)

/** Returned when no valid command is available. */
#define CMD_POS_NONE          ((uint8_t)0x00U)

/**
 * @brief Initialise the command parser module.
 *        Clears internal state and readies UART reception.
 *        [SWE-REQ-020]
 */
void CommandParser_Init(void);

/**
 * @brief Process incoming UART data (call cyclically from main loop).
 *        Reads one byte via HAL, validates against the allowed position table,
 *        and stores latest valid command (latest-wins, SWE-REQ-003).
 *        Invalid / unsupported bytes are silently discarded (SWE-REQ-002).
 *        [SWE-REQ-001, SWE-REQ-022]
 */
void CommandParser_Process(void);

/**
 * @brief Retrieve the latest validated command.
 * @param[out] p_position  Pointer to store the position value.
 * @param[out] p_valid     Pointer to store the validity flag.
 *        [SWE-REQ-001, SWE-REQ-003]
 */
void CommandParser_GetLatestCommand(uint8_t *p_position, bool *p_valid);

/**
 * @brief Clear / acknowledge the latest command after it has been consumed.
 */
void CommandParser_ClearCommand(void);

#endif /* COMMAND_PARSER_H */
