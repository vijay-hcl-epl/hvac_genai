#ifndef UART_HANDLER_H
#define UART_HANDLER_H
#include <stdint.h>
#include <stdbool.h>
void uart_handler_init(void);
void uart_rx_callback(uint8_t data);
bool uart_get_valid_command(uint8_t *command_out);
void uart_clear_error(void);
bool uart_has_error(void);
#endif // UART_HANDLER_H
