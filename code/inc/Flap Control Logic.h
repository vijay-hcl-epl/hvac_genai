#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdbool.h>
#include "Feedback Processor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-025, SWE-REQ-031, SWE-REQ-032, SWE-REQ-033 */

typedef enum
{
    FLAP_CONTROL_STATE_IDLE = 0,
    FLAP_CONTROL_STATE_MOVING,
    FLAP_CONTROL_STATE_TARGET_REACHED,
    FLAP_CONTROL_STATE_FAULT
} FlapControl_State_t;

void FlapControlLogic_Init(void);
void FlapControlLogic_Task(void);
void FlapControlLogic_IssueMovementCmd(Hvac_FlapPosition_t target_pos);
FlapControl_State_t FlapControlLogic_GetState(void);
bool FlapControlLogic_IsInMotion(void);

#ifdef __cplusplus
}
#endif

#endif /* FLAP_CONTROL_LOGIC_H */
