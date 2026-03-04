#ifndef USER_CMD_HANDLER_H
#define USER_CMD_HANDLER_H
#include <stdint.h>
#include <stdbool.h>
void CMDH_ProcessUART(void);
uint8_t CMDH_GetTargetPosition(void);
bool CMDH_HasNewCommand(void);
#endif // USER_CMD_HANDLER_H
