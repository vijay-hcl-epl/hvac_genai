#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

typedef enum
{
    FLAP_CONTROL_STATE_IDLE = 0,
    FLAP_CONTROL_STATE_MOVING,
    FLAP_CONTROL_STATE_TARGET_REACHED,
    FLAP_CONTROL_STATE_FAULT
} FlapControl_StateType;

void FlapControl_Init(void);
void FlapControl_IssueMovementCmd(uint8_t target_pos);
void FlapControl_Task(void);
FlapControl_StateType FlapControl_GetState(void);
uint8_t FlapControl_GetTargetPosition(void);

#endif /* FLAP_CONTROL_LOGIC_H */
