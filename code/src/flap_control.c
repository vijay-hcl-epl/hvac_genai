#include "flap_control.h"
#include "motor_control.h"
#include "feedback_acquisition.h"
#include "status_indication.h"

#define FLAP_POSITIONS  5
static uint8_t valid_positions[FLAP_POSITIONS] = {0,1,2,3,4};
static uint8_t target_position = 0;
static uint8_t current_position = 0xFF;

void flap_control_init(void) {
    // No dynamic setup required
    target_position = 0xFF;
}

void set_target_position(uint8_t pos) {
    // Check if valid position
    int found = 0;
    for (int i=0; i<FLAP_POSITIONS; ++i) {
        if (valid_positions[i] == pos) found = 1;
    }
    if (!found) {
        status_indication_set_error(true);
        return;
    }
    if (pos == current_position) return;
    // Command to motor control
    flap_dir_t dir = (pos > current_position) ? FLAP_UP : FLAP_DOWN;
    motor_run(dir);
    // Wait for feedback, simplified as direct call
    current_position = feedback_acquisition_get_position();
    if (current_position == pos) {
        motor_stop();
        status_indication_set_position(pos);
    }
}
