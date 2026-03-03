#ifndef POSITION_CONTROL_H
#define POSITION_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

// Application-specific config
#define POS_FLAP_POS_MIN 0
#define POS_FLAP_POS_MAX 5

typedef enum {
    POS_STATE_IDLE = 0,
    POS_STATE_MOVEREQ,
    POS_STATE_ERROR
} POS_State_t;

void POS_Init(void);
void POS_SetTarget(int tgt);
void POS_Process(void);
void POS_OnFeedbackUpdate(int pos, bool valid);
POS_State_t POS_GetState(void);
int POS_GetCurrentPosition(void);

#endif // POSITION_CONTROL_H
