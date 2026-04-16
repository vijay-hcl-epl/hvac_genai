#include "output_indication_unit.h"
#include <string.h>

// Responsibility: Indicate system and position status using LEDs.
void output_indication_unit_resp_0(OutputIndicationUnitData* data) {
    OutputIndicationUnitState state = STATE_UPDATE_LEDS;
    switch(state) {
        case STATE_UPDATE_LEDS:
            // Update LED state according to system/position status (stub, zeroed)
            memset(data->led_status_flags, 0, LED_FLAG_COUNT);
            break;
        default:
            break;
    }
}

// Responsibility: Ensure maximum one green LED ON at any time.
void output_indication_unit_resp_1(OutputIndicationUnitData* data) {
    OutputIndicationUnitState state = STATE_ENFORCE_SINGLE_GREEN;
    switch(state) {
        case STATE_ENFORCE_SINGLE_GREEN:
            // Check and enforce only one green LED active (stub: zeroed, set one if needed)
            int green_led_found = 0;
            for (int i = 0; i < LED_FLAG_COUNT; ++i) {
                if (data->led_status_flags[i]) {
                    if (!green_led_found) {
                        green_led_found = 1;
                    } else {
                        data->led_status_flags[i] = 0; // Force single green
                    }
                }
            }
            break;
        default:
            break;
    }
}
