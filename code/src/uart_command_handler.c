#include "uart_command_handler.h"
#include <string.h>

void uart_command_handler_resp_1(uart_command_handler_t *ctx) {
    /* On UART receive event, read byte(s) into buffer. */
    /* Stubbed: Uart RX event fills buffer elsewhere */
}

void uart_command_handler_resp_2(uart_command_handler_t *ctx) {
    /* Decode buffer content: check if data represents valid command (0-5). */
    uint8_t v = ctx->uart_rx_buffer[0];
    if(v <= 5u) {
        ctx->command_valid = 1u;
    } else {
        ctx->command_valid = 0u;
    }
}

void uart_command_handler_resp_3(uart_command_handler_t *ctx) {
    /* If valid: pass to control logic; if invalid: ignore/flush buffer, no acknowledge */
    if(ctx->command_valid == 0u) {
        (void)memset(ctx->uart_rx_buffer, 0, sizeof(ctx->uart_rx_buffer));
    }
}
