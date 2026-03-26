#ifndef USER_COMMAND_IF_H
#define USER_COMMAND_IF_H
#include <stdint.h>
void UserCommandIF_Init(void);
void UserCommandIF_RxHandler(uint8_t byte);
void UserCommandIF_Process(void);
void UserCommandIF_IssueACK(void);
void UserCommandIF_IssueNACK(void);
uint8_t UserCommandIF_GetLastCommand(void);
#endif
