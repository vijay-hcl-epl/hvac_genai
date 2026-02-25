#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>

#define UART_RX_BUF_SIZE 16

enum cmd_state { CMD_VALID, CMD_INVALID };

void command_handler_init(void);
void command_handler_rx_isr(uint8_t byte);
uint8_t get_validated_cmd(void);
void reset_command_handler(void);

#endif // COMMAND_HANDLER_H
