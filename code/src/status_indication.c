#include "status_indication.h"

#define NUM_POSITIONS 6
// [TBD — GPIO mapping for LEDs from Infineon TLE9851QXW]

static int last_active_led = -1;

void power_led_on(void) {
    // TODO: Set power LED ON
    // [TBD - Assign actual pin/register from datasheet]
}

void update_status_leds(int position) {
    // TODO: Set only the LED corresponding to current position ON
    // [TBD - Assign actual pins/registers for each LED]
    last_active_led = position;
}
