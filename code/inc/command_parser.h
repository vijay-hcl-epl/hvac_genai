/**
 * @file command_parser.h
 * @brief Command Parser – UART byte parsing and validation for flap position commands.
 *
 * Software Unit : Command Parser
 * Traceability  : SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022
 *
 * NOTE – Pin/peripheral assignments (USART instance, GPIO AF) are documented as
 *        configurable placeholders derived from env-setup.  Actual board-level
 *        mapping must be confirmed during integration.
 */
#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

/* ── Position command encoding ──────────────────────────────────────────────
 * CONFIGURATION GAP: The exact single-byte values that map to each flap
 * position are NOT specified in the requirements or env-setup.  The values
 * below are assumed defaults and MUST be validated against the actual
 * system-level command specification before deployment.
 * ──────────────────────────────────────────────────────────────────────── */
#define CMD_POS_0       ((uint8_t)0x00U)  /* Fully closed              */
#define CMD_POS_1       ((uint8_t)0x01U)  /* Position 1 (25 %)         */
#define CMD_POS_2       ((uint8_t)0x02U)  /* Position 2 (50 %)         */
#define CMD_POS_3       ((uint8_t)0x03U)  /* Position 3 (75 %)         */
#define CMD_POS_4       ((uint8_t)0x04U)  /* Fully open                */
#define CMD_POSITION_COUNT  ((uint8_t)5U)

/* Command parser states (LLD §3) */
typedef enum
{
    CMDPARSER_STATE_INIT    = 0U,
    CMDPARSER_STATE_WAIT_RX = 1U,
    CMDPARSER_STATE_VALID   = 2U,
    CMDPARSER_STATE_INVALID = 3U
} CmdParser_State_t;

/* Command result structure */
typedef struct
{
    uint8_t           position;   /* Last validated position byte        */
    uint8_t           valid;      /* 1 = valid command available, 0 = no */
    CmdParser_State_t state;      /* Current parser state                */
} CmdParser_Result_t;

/**
 * @brief Initialise the command parser (sets state to WAIT_RX).
 *        Shall be called once during system startup.
 * Trace: SWE-REQ-020 (via System Init)
 */
void CmdParser_Init(void);

/**
 * @brief Process incoming UART data.  Call this each time a byte is
 *        available from the UART peripheral.
 *        Latest-wins semantics (SWE-REQ-003).
 * Trace: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-022
 *
 * @param rx_byte  The byte received from UART.
 */
void CmdParser_ProcessByte(uint8_t rx_byte);

/**
 * @brief Retrieve the latest validated command.
 * Trace: SWE-REQ-001, SWE-REQ-015
 *
 * @param[out] p_result  Pointer to result struct (position + valid flag).
 */
void CmdParser_GetLatestCommand(CmdParser_Result_t *p_result);

/**
 * @brief Clear the valid-command flag after it has been consumed.
 * Trace: SWE-REQ-003
 */
void CmdParser_ClearCommand(void);

#endif /* COMMAND_PARSER_H */
