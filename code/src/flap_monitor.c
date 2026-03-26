#include "flap_monitor.h"

static int8_t current_position = 0;

void update_flap_feedback(int8_t new_position) {
    // Updates position value for external feedback/monitoring
    current_position = new_position;
}

int8_t get_current_flap_feedback(void) {
    return current_position;
}
