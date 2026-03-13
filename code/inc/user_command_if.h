#ifndef USER_COMMAND_IF_H
#define USER_COMMAND_IF_H

#include <stdint.h>

#define CMD_BUFFER_SIZE   8
#define CMD_POS_MIN       0
#define CMD_POS_MAX       5
#define UART_OK           0x00
#define UART_ERR          0x01

void UserCommandIF_Init(void);
void UserCommandIF_Process(void);
void UserCommandIF_RxISR(uint8_t byte);
uint8_t UserCommandIF_GetCmd(void);
uint8_t UserCommandIF_GetStatus(void);

#endif // USER_COMMAND_IF_H
