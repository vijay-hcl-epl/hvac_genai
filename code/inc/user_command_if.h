// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf §19 (UART/LIN)
#ifndef USER_COMMAND_IF_H
#define USER_COMMAND_IF_H
#include <stdint.h>
void Cmd_Received(uint8_t position);
void Cmd_Error(uint8_t reason);
void UserCommandIF_Init(void);
#endif
