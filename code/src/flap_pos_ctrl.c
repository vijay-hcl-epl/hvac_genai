#include "flap_pos_ctrl.h"
#include "pos_fb_acq.h"
#include "motor_ctrl.h"
#include "led_stat.h"
#define NUM_POS 6
static uint8_t curr_pos = 0;
static uint8_t target_pos = 0;
static enum { CTRL_IDLE, CTRL_MOVING, CTRL_ERROR } ctrl_state = CTRL_IDLE;

void flap_pos_ctrl_init(void) { curr_pos = pos_fb_acq_get_position(); ctrl_state = CTRL_IDLE; led_stat_set_led(curr_pos); }

void flap_pos_ctrl_set_target(uint8_t p) {
    if (ctrl_state != CTRL_IDLE || p > 5) return;
    target_pos = p;
    if (curr_pos == target_pos) {
        ctrl_state = CTRL_IDLE;
        return;
    }
    if (curr_pos < target_pos) {
        motor_ctrl_start(MOTOR_DIR_CW);
    } else {
        motor_ctrl_start(MOTOR_DIR_CCW);
    }
    ctrl_state = CTRL_MOVING;
}
bool flap_pos_ctrl_movement_complete(void) {
    if (ctrl_state == CTRL_MOVING) {
        uint8_t actual_pos = pos_fb_acq_get_position();
        if (actual_pos == target_pos) {
            motor_ctrl_stop();
            curr_pos = target_pos;
            led_stat_set_led(curr_pos);
            ctrl_state = CTRL_IDLE;
            return true;
        }
    }
    return (ctrl_state == CTRL_IDLE);
}
uint8_t flap_pos_ctrl_get_status(void) { return curr_pos; }
