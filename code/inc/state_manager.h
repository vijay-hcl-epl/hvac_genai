#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

typedef enum {
    STATE_IDLE = 0,
    STATE_MOVING,
    STATE_HOLDING
} state_manager_state_t;

void state_manager_init(void);
void state_manager_set_state(state_manager_state_t state);
state_manager_state_t state_manager_get_state(void);

#endif // STATE_MANAGER_H
