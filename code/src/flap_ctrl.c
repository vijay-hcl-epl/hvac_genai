#include "flap_ctrl.h"
#include "cmd_input.h"
#include "feedback_acq.h"
#include "motor_act.h"
#include "status_ind.h"

static uint8_t current_position = 0;
static uint8_t target_position = 0;
static uint8_t controller_state = 0; // 0: Idle, 1: Moving, 2: Error

int position_controller_execute(void) {
    uint8_t cmd = get_decoded_command();
    uint8_t pos = get_flap_position();
    
    if (controller_state == 2 || pos == FLAP_POS_INVALID) {
        motor_stop();
        controller_state = 2;
        set_led_state(6); // Error/idle: only power LED on
        return FLAP_CTRL_ERROR;
    }

    // Only react to new command if idle and command in range
    if (controller_state == 0 &&
        cmd != CMD_INVALID && cmd <= FLAP_POS_MAX && cmd != current_position) {
        target_position = cmd;
        controller_state = 1;
    }
    
    if (controller_state == 1) {
        if (pos < target_position) {
            motor_move(1); // 1=FWD
        } else if (pos > target_position) {
            motor_move(0); // 0=REV
        } else {
            motor_stop();
            controller_state = 0;
            current_position = pos;
            set_led_state(current_position);
        }
    }
    return FLAP_CTRL_OK;
}
