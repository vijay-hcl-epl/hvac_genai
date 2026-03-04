#include "position_ctrl_logic.h"
#include "motor_control.h"

// Control parameters
static int target_pos = -1;
static int cur_pos = -1;
static ctrl_state_t ctrl_state = CTRL_STATE_IDLE;
static int tolerance = 1;

void ctrl_logic_set_target(int pos) {
    target_pos = pos;
}

void ctrl_logic_update_feedback(int pos) {
    cur_pos = pos;
    if (target_pos < 0) return;
    if (cur_pos == target_pos || (tolerance && (cur_pos >= (target_pos-tolerance)) && (cur_pos <= (target_pos+tolerance)))) {
        // Hold position
        ctrl_state = CTRL_STATE_HOLD;
        motor_control_stop();
    } else if (cur_pos < target_pos) {
        ctrl_state = CTRL_STATE_MOVING_FWD;
        motor_control_move(MOTOR_DIR_FWD);
    } else if (cur_pos > target_pos) {
        ctrl_state = CTRL_STATE_MOVING_REV;
        motor_control_move(MOTOR_DIR_REV);
    } else {
        ctrl_state = CTRL_STATE_ERROR;
        motor_control_stop();
    }
}

int ctrl_logic_get_state(void) {
    return (int)ctrl_state;
}

void ctrl_logic_reset(void) {
    ctrl_state = CTRL_STATE_IDLE;
    target_pos = -1;
    cur_pos = -1;
}
