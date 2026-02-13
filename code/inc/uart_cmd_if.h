#ifndef UART_CMD_IF_H
#define UART_CMD_IF_H
#include <stdint.h>
#include <stdbool.h>

void uart_cmd_if_init(void);
bool uart_cmd_if_parsed_cmd_available(void);
uint8_t uart_cmd_if_get_command(void);
void uart_cmd_if_rx_handler(void);

#endif // UART_CMD_IF_H
