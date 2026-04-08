#include "Status_Indicator.h"

void Status_Indicator_Init(StatusIndicator_t *si) {
    si->red_led = LED_OFF;
    si->green_led = LED_OFF;
    si->position = 0;
}

void Status_Indicator_Update(StatusIndicator_t *si, int position, int power_on) {
    if (power_on) {
        si->red_led = LED_RED;
        si->green_led = LED_GREEN;
        si->position = position;
    } else {
        si->red_led = LED_OFF;
        si->green_led = LED_OFF;
    }
}
