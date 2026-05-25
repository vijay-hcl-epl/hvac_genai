#include "control_logic.h"
#include "input_handler.h"
#include "position_sensor_interface.h"

#define CONTROL_TOLERANCE 2

typedef enum {
    STATE_IDLE,
    STATE_MOVING,
    STATE_AT_TARGET,
    STATE_ERROR
} control_state_t;

static int target_position = 0;
static int current_position = 0;
static control_state_t control_state = STATE_IDLE;

void control_logic_init(void) {
    target_position = input_handler_get_last_valid();
    current_position = position_sensor_read();
    control_state = STATE_IDLE;
}

void control_logic_command(int tgt) {
    if (!input_handler_validate(tgt)) {
        control_logic_error();
        return;
    }
    target_position = tgt;
    control_state = STATE_MOVING;
}

void control_logic_update_position(int pos) {
    current_position = pos;
    if (control_state == STATE_MOVING) {
        if (abs(current_position - target_position) <= CONTROL_TOLERANCE) {
            control_state = STATE_AT_TARGET;
        }
    }
}

void control_logic_error(void) {
    control_state = STATE_ERROR;
}

bool control_logic_is_at_target(void) {
    return control_state == STATE_AT_TARGET;
}
