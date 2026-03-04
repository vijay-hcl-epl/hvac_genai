#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include <stdint.h>
#include <stddef.h>

int CommandDispatcher_ReceiveCommand(const uint8_t* data, size_t len);
int CommandDispatcher_GetNextTarget(int* pos_out);
void CommandDispatcher_NotifyIdle(void);

#endif // COMMAND_DISPATCHER_H
