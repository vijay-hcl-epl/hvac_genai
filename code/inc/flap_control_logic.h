#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

typedef enum {
    FLAP_STATE_IDLE = 0,
    FLAP_STATE_MOVING,
    FLAP_STATE_SAFE,
    FLAP_STATE_ERROR
} FlapControlState_t;

void FlapControlLogic_Init(void);
void FlapControlLogic_SetTarget(uint8_t position);
uint8_t FlapControlLogic_GetTarget(void);
uint8_t FlapControlLogic_GetActual(void);
FlapControlState_t FlapControlLogic_GetState(void);
void FlapControlLogic_Process(void);

#endif // FLAP_CONTROL_LOGIC_H
