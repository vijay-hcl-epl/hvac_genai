#ifndef USERCMDHANDLER_H
#define USERCMDHANDLER_H
#include <stdint.h>
/* MISRA: Rule 20.10 – Include only standard headers that are required */
void UserCmdHandler_Init(void);
void UserCmdHandler_OnUartRx(uint8_t rx_value);
#endif /* MISRA: Rule 20.5 – Preprocessor #endif should have comment */
