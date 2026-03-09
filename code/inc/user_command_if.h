#ifndef USER_COMMAND_IF_H
#define USER_COMMAND_IF_H
#include <stdint.h>

void UserCommandIF_Init(void);
void UserCommandIF_RXHandler(uint8_t data);
void UserCommandIF_Process(void);
void UserCommandIF_SendAck(void);
void UserCommandIF_SendNack(void);
uint8_t UserCommandIF_GetCommand(void);
uint8_t UserCommandIF_GetStatus(void);

#endif // USER_COMMAND_IF_H
