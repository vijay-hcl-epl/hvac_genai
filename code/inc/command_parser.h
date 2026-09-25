/**
 * @file command_parser.h
 * @brief Command Parser – UART byte parsing and validation for flap position commands.
 *
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 * Platform: STM32F407G-DISC1 / STM32 HAL
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

/** Number of supported flap positions */
#define CMD_NUM_POSITIONS       (5U)

/** Position command byte values (sent from PC over UART) */
#define CMD_POS_1               (0x01U)
#define CMD_POS_2               (0x02U)
#define CMD_POS_3               (0x03U)
#define CMD_POS_4               (0x04U)
#define CMD_POS_5               (0x05U)

/** Invalid / no-command sentinel */
#define CMD_INVALID             (0xFFU)

/**
 * @brief Initialise the command parser internal state.
 *        Must be called once before any other command_parser API.
 */
void command_parser_init(void);

/**
 * @brief Process incoming UART data (poll / call periodically).
 *        Reads one byte from UART; if valid, stores as latest command (latest wins).
 *        Invalid / unsupported bytes are silently discarded.
 */
void command_parser_update(void);

/**
 * @brief Retrieve the latest validated command.
 * @param[out] p_position  Pointer to store the position value (1–5).
 * @return 1 if a valid unread command is available, 0 otherwise.
 *         After a successful read the internal flag is cleared.
 */
uint8_t command_parser_get_latest(uint8_t *p_position);

#endif /* COMMAND_PARSER_H */
