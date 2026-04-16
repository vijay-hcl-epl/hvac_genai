#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H

#include <stdint.h>

typedef struct {
    uint8_t uart_rx_buffer[8];
    uint8_t (*decode_func)(uint8_t *);
    uint8_t command_valid;
} uart_command_handler_t;

typedef enum {
    WAIT_FOR_COMMAND,
    COMMAND_RECEIVED
} uart_cmd_state_e;

typedef enum {
    DECODE_COMMAND,
    VALID_COMMAND,
    INVALID_COMMAND
} uart_decode_state_e;

typedef enum {
    ON_INVALID,
    IGNORE_CYCLE,
    FLUSH_INPUT
} uart_invalid_state_e;

void uart_command_handler_resp_1(uart_command_handler_t *ctx);
void uart_command_handler_resp_2(uart_command_handler_t *ctx);
void uart_command_handler_resp_3(uart_command_handler_t *ctx);

#endif
