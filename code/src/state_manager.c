#include "state_manager.h"

static state_manager_state_t current_state = STATE_IDLE;

void state_manager_init(void)
{
    current_state = STATE_IDLE;
}

void state_manager_set_state(state_manager_state_t state)
{
    // Optionally add invalid transition checks
    current_state = state;
}

state_manager_state_t state_manager_get_state(void)
{
    return current_state;
}
