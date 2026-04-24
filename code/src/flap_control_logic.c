#include "flap_control_logic.h"
#include "position_status_monitor.h"
#include <stdbool.h>

static int last_target = 0;
static bool moving = false;
static bool safe_mode = false;

void flap_control_init(void) {
    moving = false;
    safe_mode = false;
    last_target = 0;
}

void flap_control_start_move(int target_pos) {
    if(!safe_mode && position_status_get_status() == POS_STATUS_NORMAL) {
        last_target = target_pos;
        moving = true;
        // Start actuation - pseudocode
        // motor_run_to(last_target);
    }
}

void flap_control_stop(void) {
    moving = false;
    // Stop motor
}

bool flap_control_is_safe(void) {
    return !safe_mode;
}

bool flap_control_is_at_target(void) {
    return (position_status_get() == last_target);
}

bool flap_control_is_fault(void) {
    if(position_status_get_status() == POS_STATUS_OUT_OF_RANGE) {
        safe_mode = true;
        flap_control_stop();
        return true;
    }
    return false;
}
