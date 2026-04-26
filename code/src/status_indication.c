#include "status_indication.h"
#include <stdbool.h>

static uint8_t indicator_flags = 0;

void status_indication_init(void) {
    indicator_flags = 0;
}

void update_indicators(uint8_t state_flags) {
    indicator_flags = state_flags;
    // ToDo: Hardware-specific code to update LEDs.
}

void indicate_power_on(void) {
    // Power LED ON
}

void indicate_position(unsigned int logical_position) {
    // Green LEDs logic: only one ON at a time
}

void indicate_error(bool error_active) {
    // Error LED logic
}
