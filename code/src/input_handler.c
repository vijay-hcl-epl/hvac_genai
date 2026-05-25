#include "input_handler.h"

static int last_valid_input = FLAP_POSITION_MIN;

bool input_handler_validate(int input_value) {
    if (input_value >= FLAP_POSITION_MIN && input_value <= FLAP_POSITION_MAX) {
        last_valid_input = input_value;
        return true;
    }
    // Trigger safe state (could signal control logic)
    return false;
}

int input_handler_get_last_valid(void) {
    return last_valid_input;
}
