#include "main_control_logic.h"
#include "motor_actuator.h"
#include "position_feedback.h"
#include "indicator_control.h"

static uint8_t target_pos = 0;
static uint8_t actual_pos = 0;
static enum {IDLE, MOVING, ERROR} state;
static bool move_in_progress = false;

void main_control_logic_init(void)
{
    state = IDLE;
    move_in_progress = false;
    target_pos = 0;
    actual_pos = 0;
    motor_actuator_stop();
    indicator_control_init();
}

void main_control_logic_on_cmd(uint8_t pos, bool valid)
{
    if (!valid || state == ERROR) return;
    if (pos != actual_pos) {
        target_pos = pos;
        state = MOVING;
        move_in_progress = true;
        motor_actuator_move();
        indicator_control_update(IDLE, target_pos, move_in_progress);
    }
}

void main_control_logic_on_feedback(uint8_t pos, bool in_range)
{
    actual_pos = pos;
    if (!in_range) {
        state = ERROR;
        move_in_progress = false;
        motor_actuator_stop();
        indicator_control_update(ERROR, actual_pos, move_in_progress);
        return;
    }
    if (state == MOVING && actual_pos == target_pos) {
        move_in_progress = false;
        motor_actuator_stop();
        state = IDLE;
    }
    indicator_control_update(state, actual_pos, move_in_progress);
}

void main_control_logic_on_error(void)
{
    state = ERROR;
    move_in_progress = false;
    motor_actuator_stop();
    indicator_control_update(ERROR, actual_pos, move_in_progress);
}

void main_control_logic_run(void)
{
    // Empty stub; expand for periodic tasks as needed
}
