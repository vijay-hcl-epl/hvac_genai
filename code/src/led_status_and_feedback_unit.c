#include "led_status_and_feedback_unit.h"
#include <string.h>

// Indicate power and flap position using LEDs
void led_status_resp_1(LedStatusData_t *data, bool power_on) {
    data->power_led = power_on;
}

// Set green LED for current flap position, all others OFF
void led_status_resp_2(LedStatusData_t *data, uint8_t position, bool valid) {
    memset(data->position_leds, 0, sizeof(data->position_leds));
    if (valid && position < MAX_POSITION_LEDS) {
        data->position_leds[position] = true;
    }
}
