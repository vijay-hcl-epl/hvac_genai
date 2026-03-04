#include "status_led_indication.h"
#include <stdint.h>

// Stub for hardware LED update
static void set_leds(int pos, int error) {
    // Replace: set GPIOs to light correct combination
}

void led_indication_update(int pos, int error) {
    set_leds(pos, error);
}

void led_indication_error(void) {
    set_leds(-1, 1);
}
