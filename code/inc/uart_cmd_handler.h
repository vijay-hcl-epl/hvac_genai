#ifndef UART_CMD_HANDLER_H
#define UART_CMD_HANDLER_H

#include <stdint.h>

void uart_cmd_init(void);
int8_t uart_cmd_get(void);

#endif // UART_CMD_HANDLER_H
/* MISRA: Rule 20.3 – Ending preprocessor directives with comments for readability */
