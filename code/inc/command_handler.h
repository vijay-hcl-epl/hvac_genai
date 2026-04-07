#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
typedef enum { CMD_ACCEPTED, CMD_IGNORED, CMD_BUSY } CmdStatus_t;
CmdStatus_t validate_and_dispatch(uint8_t cmd);
void command_handler_init(void);
#endif // COMMAND_HANDLER_H
