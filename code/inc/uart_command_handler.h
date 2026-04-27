#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define UART_CMD_MAX_LEN 8

// Notifies control logic of a new flap position
void uart_command_handler_init(void);
void uart_command_handler_rx_byte(uint8_t byte);

#endif // UART_COMMAND_HANDLER_H
