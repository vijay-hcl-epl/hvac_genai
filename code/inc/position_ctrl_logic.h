#ifndef POSITION_CTRL_LOGIC_H
#define POSITION_CTRL_LOGIC_H
#include <stdint.h>
void POSC_Update(void);
void POSC_SetTarget(uint8_t pos);
uint8_t POSC_GetCurrentState(void);
#endif // POSITION_CTRL_LOGIC_H
