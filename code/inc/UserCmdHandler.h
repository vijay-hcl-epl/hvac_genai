#ifndef USERCMDHANDLER_H
#define USERCMDHANDLER_H
#include <stdint.h>
void UserCmdHandler_Init(void);
void UserCmdHandler_OnUartRx(uint8_t rx_value);
#endif // USERCMDHANDLER_H
