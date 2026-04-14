#include "flap_control_logic.h"
#include "motor_driver.h"
#include "led_status_handler.h"
#include "feedback_processor.h"

static uint8_t current_pos = 0;
static uint8_t last_cmd_pos = 0;
static bool in_motion = false;
static flap_ctrl_state_t state = FLAP_IDLE;

static const uint8_t position_limits[2] = {0x10, 0x40}; // Example

void flap_control_init(void) {
    current_pos = 0;
    last_cmd_pos = 0;
    in_motion = false;
    state = FLAP_IDLE;
}

void flap_control_new_command(uint8_t pos, bool valid) {
    if (!valid) return;
    if (pos == current_pos) {
        in_motion = false;
        state = FLAP_TARGET_REACHED;
        motor_stop();
        led_position_set(pos);
    } else {
        last_cmd_pos = pos;
        in_motion = true;
        state = FLAP_MOVING;
        // Decide direction
        int8_t delta = (int8_t)pos - (int8_t)current_pos;
        motor_drive((delta > 0) ? MOTOR_DIR_FWD : MOTOR_DIR_REV, true);
    }
}

void flap_control_feedback_update(uint8_t pos, bool valid) {
    if (!valid) {
        state = FLAP_FAULT;
        in_motion = false;
        motor_stop();
        led_indicate_error();
        return;
    }
    current_pos = pos;
    if (in_motion && (pos == last_cmd_pos)) {
        in_motion = false;
        state = FLAP_TARGET_REACHED;
        motor_stop();
        led_position_set(pos);
    }
}

void flap_control_task(void) {
    // Can be expanded for periodic checks, FAULT recovery, etc.
    if (state == FLAP_FAULT) {
        // Fault recovery (implement if needed)
    }
}
