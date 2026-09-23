/**
 * @file    command_parser.h
 * @brief   Command Parser software unit – header.
 *
 * Parses incoming UART bytes, validates against allowed flap position
 * commands, and stores the latest valid command (latest-wins).
 *
 * Traceability:
 *   SWE-REQ-001  – Process single-byte UART commands for target flap positions.
 *   SWE-REQ-002  – Ignore / do not acknowledge unsupported commands.
 *   SWE-REQ-003  – Support exactly one queued command (latest wins).
 *   SWE-REQ-015  – Receive commands via logical UART interface.
 *   SWE-REQ-022  – Constantly monitor for new UART user command inputs.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *   SWE-REQ-038  – All limits declared statically.
 *   SWE-REQ-041  – Structure code to facilitate verification.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL. MISRA-style C.
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/* ---- Public Types --------------------------------------------------- */

/** @brief States of the Command Parser state machine (LLD §3 SM). */
typedef enum
{
    CMD_STATE_INIT    = 0U,   /**< Initial / not yet started            */
    CMD_STATE_WAIT_RX,        /**< Waiting for a UART byte              */
    CMD_STATE_VALID,          /**< Last received byte was a valid cmd   */
    CMD_STATE_INVALID         /**< Last received byte was invalid       */
} CommandParserState_t;

/** @brief Command data structure – static, single-slot (SWE-REQ-003). */
typedef struct
{
    uint8_t              position;   /**< Latest valid target position   */
    bool                 valid;      /**< True if position holds a valid cmd */
    CommandParserState_t state;      /**< Current parser state           */
} CommandData_t;

/* ---- Public Constants ----------------------------------------------- */

/** @brief Number of supported flap positions (statically declared).
 *  Positions 0..4 map to: CLOSED, 25 %, 50 %, 75 %, FULLY_OPEN.
 *  [SWE-REQ-038, SWE-REQ-030]                                        */
#define CMD_NUM_POSITIONS  (5U)

/** @brief UART command byte values for each position (configurable).
 *  Index corresponds to logical position 0..4.                        */
extern const uint8_t CMD_ALLOWED_TABLE[CMD_NUM_POSITIONS];

/* ---- Public API ----------------------------------------------------- */

/**
 * @brief  Initialise the command parser (sets state to WAIT_RX, clears data).
 *         [SWE-REQ-020]
 */
void CommandParser_Init(void);

/**
 * @brief  Process incoming UART data (call from main loop).
 *         Reads one byte via HAL UART; validates against allowed table.
 *         [SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-022]
 */
void CommandParser_Process(void);

/**
 * @brief  Retrieve latest command.
 * @param[out] pPosition  Pointer to receive target position (0..4).
 * @return true if a valid, unconsumed command is available; false otherwise.
 *         [SWE-REQ-001, SWE-REQ-003]
 */
bool CommandParser_GetLatestCommand(uint8_t *pPosition);

/**
 * @brief  Clear the valid-flag after consumer has read the command.
 *         [SWE-REQ-003]
 */
void CommandParser_ConsumeCommand(void);

#endif /* COMMAND_PARSER_H */
