#include "state_manager.h"
#include "status_indication.h"

static system_state_t current_state = STATE_IDLE;

void StateManager_Init(void) {
    current_state = STATE_IDLE;
}

void StateManager_SetState(system_state_t s) {
    current_state = s;
    StatusIndication_UpdateOnState(current_state);
}

system_state_t StateManager_GetState(void) {
    return current_state;
}

void StateManager_OnNewCommand(void) {
    if (current_state == STATE_IDLE || current_state == STATE_STEADY) {
        StateManager_SetState(STATE_MOVING);
    }
}

void StateManager_OnTargetReached(void) {
    if (current_state == STATE_MOVING) {
        StateManager_SetState(STATE_STEADY);
    }
}

void StateManager_OnError(void) {
    StateManager_SetState(STATE_ERROR);
}
