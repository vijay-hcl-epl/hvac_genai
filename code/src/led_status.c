#include "led_status.h"
// Simulated GPIO state
static uint8_t leds[6];
void led_status_init(void) { for (int i = 0; i < 6; ++i) leds[i] = 0; }
void led_status_power_on(void) { leds[0] = 1; /* Power LED ON pattern */ }
void led_status_update_position(uint8_t pos)
{
    for (int i = 0; i < 6; ++i) leds[i] = 0;
    if (pos < 6) leds[pos] = 1;
}
void led_status_error(void) { for (int i = 0; i < 6; ++i) leds[i] = 1; /* All on = error! */ }
