#include "state_manager.h"
static SystemState g_sys_state = STATE_IDLE;
void StateMgr_update(uint8_t event) {
    // [TBD — Implement full FSM per arch/SWE-1]
    if (event == 0) g_sys_state = STATE_IDLE;
    else if (event == 1) g_sys_state = STATE_MOVING;
    else if (event == 2) g_sys_state = STATE_TARGET;
    else if (event == 3) g_sys_state = STATE_FAULT;
    else if (event == 4) g_sys_state = STATE_SLEEP;
}
SystemState StateMgr_status(void) { return g_sys_state; }
