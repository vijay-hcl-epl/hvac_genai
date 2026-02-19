#include "flap_control_logic.h"
#include "position_feedback.h"
#include "motor_driver_interface.h"
#include "configuration_data.h"
#include "error_handling.h"

static uint16_t cur_position = 0;
static uint16_t tgt_position = 0;
static flap_state_t flap_state = FLAP_IDLE;

void flap_control_logic_init(void) {
    configuration_t* cfg = configuration_data_get();
    flap_state = FLAP_IDLE;
    tgt_position = cfg->clamp_min;
    cur_position = cfg->clamp_min;
}

void flap_control_logic_update_target(uint16_t pos) {
    configuration_t* cfg = configuration_data_get();
    // Clamp
    if (pos < cfg->clamp_min) pos = cfg->clamp_min;
    if (pos > cfg->clamp_max) pos = cfg->clamp_max;
    tgt_position = pos;
    flap_state = FLAP_MOVING;
}

flap_state_t flap_control_logic_get_state(void) {
    return flap_state;
}

void flap_control_logic_periodic(void) {
    configuration_t* cfg = configuration_data_get();
    cur_position = position_feedback_get_position();
    bool plausible = position_feedback_is_plausible();
    if (!plausible) {
        error_handling_set_error(ERR_POSITION_IMPLAUSIBLE);
        flap_state = FLAP_ERROR;
        motor_driver_interface_stop_motor();
        return;
    }
    if (flap_state == FLAP_MOVING) {
        // Assume tolerance of =2 units
        if (cur_position < tgt_position - 2) {
            motor_driver_interface_set_motor(MOTOR_DIR_FORWARD, 80);
        } else if (cur_position > tgt_position + 2) {
            motor_driver_interface_set_motor(MOTOR_DIR_REVERSE, 80);
        } else {
            flap_state = FLAP_TARGET_REACHED;
            motor_driver_interface_stop_motor();
        }
    }
}
