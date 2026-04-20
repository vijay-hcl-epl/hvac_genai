#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
#include <stdbool.h>

void uart_rx_handler(uint8_t byte_in);
int get_next_command(void);
bool is_command_ready(void);

#endif // COMMAND_HANDLER_H
