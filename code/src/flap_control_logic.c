#include "flap_control_logic.h"
#include "user_command_handler.h"
#include "motor_control_driver.h"
#include "feedback_processing.h"
#include "status_indication.h"
#include "error_safety_monitor.h"
#include "calibration_config.h"
#include <stdlib.h>

static uint16_t current_position = 0;
static uint16_t target_position = 0;
static flap_state_t state = FLAP_STATE_IDLE;
static bool command_in_progress = false;
static const uint16_t position_tolerance = 2; // Example tolerance

void flap_control_logic_init(void) {
    state = FLAP_STATE_IDLE;
    command_in_progress = false;
    current_position = feedback_processing_get_position();
    status_indication_update(current_position);
    motor_control_driver_disable();
}

void flap_control_logic_process(void) {
    uint16_t new_target;
    if (!command_in_progress && get_new_command(&new_target)) {
        target_position = new_target;
        command_in_progress = true;
        state = FLAP_STATE_MOVING;
    }
    current_position = feedback_processing_get_position();
    if (state == FLAP_STATE_MOVING) {
        if (error_safety_monitor_is_error()) {
            motor_control_driver_disable();
            state = FLAP_STATE_ERROR;
            command_in_progress = false;
            status_indication_update(current_position);
        } else if (abs((int)current_position - (int)target_position) <= position_tolerance) {
            motor_control_driver_disable();
            state = FLAP_STATE_COMPLETE;
            command_in_progress = false;
            status_indication_update(current_position);
        } else if (current_position > target_position) {
            motor_control_driver_set_direction(MOTOR_DIRECTION_REVERSE);
        } else if (current_position < target_position) {
            motor_control_driver_set_direction(MOTOR_DIRECTION_FORWARD);
        }
    }
    if (state == FLAP_STATE_ERROR) {
        // Error state, no action
        motor_control_driver_disable();
        status_indication_update(current_position);
    }
    if (state == FLAP_STATE_COMPLETE) {
        // Hold, nothing to do, can allow new commands
        status_indication_update(current_position);
        state = FLAP_STATE_IDLE;
    }
}
