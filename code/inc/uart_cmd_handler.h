#ifndef UART_CMD_HANDLER_H
#define UART_CMD_HANDLER_H

#include <stdbool.h>
#include <stdint.h>

#define UART_CMD_MAX_LEN 32

typedef enum {
    UART_CMD_IDLE,
    UART_CMD_RECEIVING,
    UART_CMD_VALIDATING,
    UART_CMD_ERROR
} uart_cmd_state_t;

typedef struct {
    char buffer[UART_CMD_MAX_LEN];
    int  len;
    bool valid;
    int  target_position;
    int  error_type;
} uart_cmd_t;

void uart_cmd_init(void);
void uart_cmd_receive_char(char c);
bool uart_cmd_issue_command(int* target_position);
int  uart_cmd_get_last_error(void);

#endif // UART_CMD_HANDLER_H
