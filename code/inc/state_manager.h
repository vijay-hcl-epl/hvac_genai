#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H
#include <stdint.h>

typedef enum {
    STATE_IDLE,
    STATE_MOVING,
    STATE_TARGET,
    STATE_FAULT,
    STATE_SLEEP
} SystemState;

void StateMgr_update(uint8_t event);
SystemState StateMgr_status(void);

#endif // STATE_MANAGER_H
