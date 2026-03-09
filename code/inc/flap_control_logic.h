#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H
#include <stdint.h>

typedef enum {
    FLAP_IDLE = 0,
    FLAP_MOVING,
    FLAP_SAFE,
    FLAP_ERROR
} FlapControlState;

void FlapControlLogic_Init(void);
void FlapControlLogic_MoveTo(uint8_t position);
void FlapControlLogic_Update(void);
FlapControlState FlapControlLogic_GetState(void);

#endif // FLAP_CONTROL_LOGIC_H
