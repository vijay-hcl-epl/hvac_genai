#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H
#include <stdint.h>
typedef enum { CMD_OK = 0, CMD_INVALID, CMD_BUSY } CmdStatus_t;
CmdStatus_t SendFlapCmdRequest(uint8_t position);
void CommandInterface_UartRxHandler(uint8_t data);
void CommandInterface_Init(void);
#endif // COMMAND_INTERFACE_H
