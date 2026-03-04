#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H
#include <stdint.h>
#include <stdbool.h>

// Status codes
#define CMD_OK      (0)
#define CMD_INVALID (1)
#define CMD_REPEATED (2)

void command_interpreter_init(void);
int  accept_command(uint8_t cmd);

#endif // COMMAND_INTERPRETER_H
