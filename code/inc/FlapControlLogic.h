#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H
#include <stdint.h>
#include <stdbool.h>

void FlapControlLogic_Init(void);
void FlapControlLogic_SetTargetPosition(uint8_t pos);
void FlapControlLogic_OnPositionFeedback(uint8_t newPos, bool valid);
void FlapControlLogic_Update(void);

#endif // FLAP_CONTROL_LOGIC_H
