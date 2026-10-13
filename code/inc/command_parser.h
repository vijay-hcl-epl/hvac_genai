/**
 * @file command_parser.h
 * @brief Command Parser – UART byte parsing and validation for flap position commands.
 *
 * Software Unit : Command Parser
 * Traces        : SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 * Platform      : STM32F407G-DISC1, STM32 HAL
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

/** Number of supported flap positions */
#define CMD_NUM_POSITIONS  ((uint8_t)5U)

/** Position command byte values (sent from PC over UART) */
#define CMD_POS_FULLY_CLOSED  ((uint8_t)0x00U)
#define CMD_POS_25_PERCENT    ((uint8_t)0x01U)
#define CMD_POS_50_PERCENT    ((uint8_t)0x02U)
#define CMD_POS_75_PERCENT    ((uint8_t)0x03U)
#define CMD_POS_FULLY_OPEN    ((uint8_t)0x04U)

/** Command parser states */
typedef enum
{
    CMD_STATE_INIT    = 0U,
    CMD_STATE_WAIT_RX,
    CMD_STATE_VALID,
    CMD_STATE_INVALID
} CmdParserState_t;

/** Command result structure */
typedef struct
{
    uint8_t          position;   /**< Last valid position command byte */
    uint8_t          valid;      /**< 1 = valid command available, 0 = none */
    CmdParserState_t state;      /**< Current parser state */
} CmdParserData_t;

/**
 * @brief Initialise the command parser module.
 * Traces: SWE-REQ-020 (called by system_init)
 */
void CommandParser_Init(void);

/**
 * @brief Process one pending UART receive byte (non-blocking).
 *        Must be called cyclically from the main loop.
 * Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-022
 */
void CommandParser_Process(void);

/**
 * @brief Retrieve the latest validated command.
 * @param[out] pPosition  Pointer to receive the position value.
 * @return 1 if a valid unread command is available, 0 otherwise.
 * Traces: SWE-REQ-001, SWE-REQ-003, SWE-REQ-015
 */
uint8_t CommandParser_GetLatestCommand(uint8_t *pPosition);

#endif /* COMMAND_PARSER_H */
