#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

// Flap control state
typedef enum {
    FLAP_IDLE = 0,
    FLAP_MOVING,
    FLAP_TARGET_REACHED,
    FLAP_FAULT
} FlapControl_State_t;

void FlapControlLogic_Init(void);
void FlapControlLogic_Task(void);
FlapControl_State_t FlapControlLogic_GetState(void);

#endif // FLAP_CONTROL_LOGIC_H
