#include "led_status_handler.h"
#include <stdio.h>

void led_status_init(void) {
    // Initialize all LEDs
}

void led_status_update(int position, bool fault) {
    // Simulate LED signaling
    if(fault) {
        led_status_error_signal();
        return;
    }
    int led_idx = position / 25;
    printf("LED %d ON (others OFF)\n", led_idx);
}

void led_status_error_signal(void) {
    printf("ERROR: LED ERROR SIGNAL\n");
}
