#ifndef USER_CMD_HANDLER_H
#define USER_CMD_HANDLER_H
#include <stdint.h>
#include <stdbool.h>

void UserCmdHandler_Process(uint8_t rx_byte);
uint8_t UserCmdHandler_GetTarget(void);
bool UserCmdHandler_HasNewTarget(void);

#endif // USER_CMD_HANDLER_H
