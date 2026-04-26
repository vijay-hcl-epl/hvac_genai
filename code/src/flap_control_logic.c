#include "flap_control_logic.h"
#include "input_management.h"
#include "position_sensing_feedback.h"
#include "status_indication.h"

static FlapState current_state = FLAP_STATE_INIT;
static unsigned int requested_position = 0;
static bool movement_in_progress = false;
static bool error_detected = false;

void flap_control_init(void) {
    current_state = FLAP_STATE_INIT;
    movement_in_progress = false;
    error_detected = false;
}

void start_move(unsigned int req_pos) {
    if (current_state == FLAP_STATE_IDLE && !movement_in_progress) {
        requested_position = req_pos;
        movement_in_progress = true;
        current_state = FLAP_STATE_MOVING;
    }
}

void stop_motor(void) {
    movement_in_progress = false;
    current_state = FLAP_STATE_HOLD;
}

void signal_error(void) {
    error_detected = true;
    current_state = FLAP_STATE_ERROR;
}

bool flap_in_error(void) {
    return error_detected;
}

void flap_control_main(void) {
    switch (current_state) {
        case FLAP_STATE_INIT:
            flap_control_init();
            current_state = FLAP_STATE_IDLE;
            break;
        case FLAP_STATE_IDLE:
            // Wait for command via Input Management
            break;
        case FLAP_STATE_MOVING:
            {
                unsigned int current_position = get_current_logical_position();
                if (!adc_in_bounds(get_adc_sample())) {
                    signal_error();
                } else if (current_position == requested_position) {
                    stop_motor();
                }
            }
            break;
        case FLAP_STATE_HOLD:
            // Maintain current position, monitor for new commands
            break;
        case FLAP_STATE_ERROR:
            indicate_error(true);
            // Attempt recovery, transition to IDLE if possible
            break;
        default:
            break;
    }
}
