#ifndef POSITION_CTRL_LOGIC_H
#define POSITION_CTRL_LOGIC_H
#include <stdint.h>
#include <stdbool.h>

void PositionCtrl_Update(void);
uint8_t PositionCtrl_GetStatus(void);
void PositionCtrl_SetTarget(uint8_t pos);
bool PositionCtrl_TargetReached(void);

#endif // POSITION_CTRL_LOGIC_H
