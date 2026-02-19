#include "flap_control.h"

void flap_control_init(flap_control_t *inst, uint8_t cur_pos)
{
    if (inst == NULL) { return; }
    inst->current_position = cur_pos;
    inst->target_position = cur_pos;
    inst->in_motion = false;
    inst->state = FLAP_IDLE;
}

bool flap_control_update(flap_control_t *inst, uint8_t cmd_pos, bool cmd_valid, uint8_t fb_pos, bool fb_valid)
{
    if (inst == NULL) { return false; }
    bool start_move = false;

    if (!cmd_valid || !fb_valid) {
        inst->in_motion = false;
        inst->state = FLAP_FAULT;
        return false;
    }

    if (cmd_pos != fb_pos) {
        inst->target_position = cmd_pos;
        inst->in_motion = true;
        inst->state = FLAP_MOVING;
        start_move = true;
    } else {
        inst->in_motion = false;
        inst->state = FLAP_TARGET_REACHED;
    }
    inst->current_position = fb_pos;
    return start_move;
}
