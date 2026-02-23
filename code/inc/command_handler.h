#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define CMD_INVALID 0xFF

void command_handler_init(void);
void command_handler_receive(uint8_t data);
bool command_handler_get_new_command(uint8_t* position);

#endif // COMMAND_HANDLER_H
