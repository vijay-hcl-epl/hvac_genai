#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <stdint.h>

typedef enum {
    STATE_IDLE,
    STATE_MOVING,
    STATE_STEADY,
    STATE_ERROR
} system_state_t;

void StateManager_Init(void);
void StateManager_SetState(system_state_t s);
system_state_t StateManager_GetState(void);
void StateManager_OnNewCommand(void);
void StateManager_OnTargetReached(void);
void StateManager_OnError(void);

#endif // STATE_MANAGER_H
