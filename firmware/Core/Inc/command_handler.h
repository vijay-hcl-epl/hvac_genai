#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>
#include <stddef.h>

#define CMD_INVALID      (0xFFU)
#define CMD_MIN          (0U)  /* Ensure 0U is not used as a null pointer constant; use NULL for pointers */
#define CMD_MAX          (5U)
#define CMD_UART_BUF_LEN (8U)

typedef enum
{
    CMD_STATE_IDLE = 0,
    CMD_STATE_COMMAND_RECEIVED,
    CMD_STATE_VALIDATED
} CmdState_t; /* Do not use CmdState_t as a bit-field type */

uint8_t CommandHandler_PollCommand(uint8_t *cmd_out);
/* In implementation, ensure NULL is used as the null pointer constant for cmd_out */

#endif /* COMMAND_HANDLER_H */