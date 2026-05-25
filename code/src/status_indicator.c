#include "status_indicator.h"
#include <stdio.h>

static led_state_t last_displayed_state = LED_OFF;

void status_indicator_update(led_state_t state) {
    last_displayed_state = state;
    // Replace with actual LED driver code
    switch (state) {
        case LED_OFF: printf("LEDs OFF\n"); break;
        case LED_MOVING: printf("LEDs MOVING\n"); break;
        case LED_AT_TARGET: printf("LEDs AT TARGET\n"); break;
        case LED_ERROR: printf("LEDs ERROR\n"); break;
    }
}
