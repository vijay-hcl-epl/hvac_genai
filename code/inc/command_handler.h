#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>

typedef enum {
    CMD_PARSE_OK,
    CMD_PARSE_INVALID,
    CMD_PARSE_EMPTY
} CmdParseStatus;

CmdParseStatus command_handler_poll(uint8_t* cmd_out);

#endif // COMMAND_HANDLER_H
