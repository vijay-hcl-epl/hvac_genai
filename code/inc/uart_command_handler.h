#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define UART_CMD_MAX_LEN 8

// Public API
typedef void (*uart_cmd_cb_t)(uint8_t position, bool valid);

void uart_command_handler_init(uart_cmd_cb_t cb);
void uart_command_handler_receive(uint8_t byte);

#endif // UART_COMMAND_HANDLER_H
