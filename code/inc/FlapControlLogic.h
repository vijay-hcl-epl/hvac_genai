#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H
#include <stdint.h>
void FlapControlLogic_Init(void);
void FlapControlLogic_Process(void);
void FlapControlLogic_SetTarget(uint8_t position);
void FlapControlLogic_OnPositionUpdate(uint8_t position);
#endif
