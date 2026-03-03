#ifndef USER_COMMAND_HANDLER_H
#define USER_COMMAND_HANDLER_H
#include <stdint.h>
#include <stdbool.h>
#define UART_RX_BUFFER_SIZE 8

bool get_new_command(uint16_t *target_position);

void user_command_handler_init(void);
void user_command_handler_poll(void);

#endif // USER_COMMAND_HANDLER_H
