#ifndef USER_CMD_HANDLER_H
#define USER_CMD_HANDLER_H

#include <stdint.h>

/* UART Command Handler States */
typedef enum {
    CMD_STATE_IDLE,
    CMD_STATE_RECEIVING,
    CMD_STATE_VALIDATED,
    CMD_STATE_ERROR
} cmd_state_t;

/** Handle incoming UART byte. */
void cmd_handler_rx_byte(uint8_t byte);

/** Obtain a valid target position (if available, returns 1 if valid, else 0). */
int cmd_handler_get_target(int* pos);

/** Reset handler (call after error). */
void cmd_handler_reset(void);

#endif // USER_CMD_HANDLER_H
