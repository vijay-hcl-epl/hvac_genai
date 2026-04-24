#include "led.h"
#include <stdint.h>
#include <stdio.h>

static bool leds[6] = {0};
static bool power_led = false;

void led_init(void) {
    for(int i=0;i<6;++i) leds[i]=false;
    power_led=false;
}

void led_update_state(bool system_on, int logical_pos, bool test_mode) {
    power_led = system_on;
    for(int i=0;i<6;++i) leds[i] = false;
    if (system_on && logical_pos >= 0 && logical_pos < 6) {
        if (!test_mode)
            leds[logical_pos] = true;
    }
    // Simulated output
    printf("[LEDs]");
    if (power_led) printf(" PWR_ON");
    for(int i=0;i<6;++i) if(leds[i]) printf(" POS%d",i);
    printf("\n");
}
