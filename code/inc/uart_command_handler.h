#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H
#include <stdbool.h>

// Status codes for UART command parser
typedef enum {
    UART_CMD_OK,
    UART_CMD_ERROR,
    UART_CMD_OOR
} uart_cmd_status_t;

// UART handler initialization
void uart_command_handler_init(void);
// RX callback interface (to be connected to HAL/driver)
void uart_rx_callback(unsigned char byte);
// Query if command is parsed & ready
bool is_command_ready(void);
// Get parsed command value (after ready=true)
int get_parsed_command(void);
// Get parser status
uart_cmd_status_t get_uart_cmd_status(void);
// Reset parser state
void uart_command_reset(void);

#endif
