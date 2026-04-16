#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H
#include <stdint.h>
#include <stdbool.h>

#define CMD_INBUF_SIZE 8

void CommandInterpreter_Init(void);
bool CommandInterpreter_Validate(const char* rx_buffer, uint8_t* valid_cmd_out);

#endif // COMMAND_INTERPRETER_H
