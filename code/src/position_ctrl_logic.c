#include "position_ctrl_logic.h"
#include "user_cmd_handler.h"
#include "feedback_acq_proc.h"
#include "motor_control.h"
#include "status_led_indication.h"
#include "system_config_data.h"

static bool moving_status = false;

void position_ctrl_logic_init(void) {
    moving_status = false;
}

void position_ctrl_step(void) {
    uint8_t target = get_last_cmd_position();
    uint8_t current = get_current_position();
    if (is_cmd_valid() && target != current) {
        // move
        motor_control_move((target > current) ? MOTOR_DIR_FWD : MOTOR_DIR_REV);
        moving_status = true;
    } else {
        motor_control_stop();
        moving_status = false;
    }
    update_led_indication(current, get_system_power_status());
}

bool get_moving_status(void) {
    return moving_status;
}
