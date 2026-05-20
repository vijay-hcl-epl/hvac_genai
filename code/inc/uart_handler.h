#ifndef UART_HANDLER_H
#define UART_HANDLER_H

void uart_init(void);
void uart_receive_handler(void);
int uart_parse_command(const char *cmd);

#endif
