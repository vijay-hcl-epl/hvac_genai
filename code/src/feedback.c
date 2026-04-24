#include "feedback.h"
#include "hardware_abstraction.h"

#define POS_LED_COUNT 6
static const int pos_led_map[POS_LED_COUNT] = {0, 1, 2, 3, 4, 5}; // abstract indices
#define POWER_LED_IDX 6

void FB_Init(void) {
    HA_SetLED(POWER_LED_IDX, 1);
    FB_UpdatePositionLED(0);
}

void FB_UpdatePositionLED(int pos) {
    for (int i = 0; i < POS_LED_COUNT; ++i)
        HA_SetLED(pos_led_map[i], (i == pos) ? 1 : 0);
}

void FB_SetPowerLED(int on) {
    HA_SetLED(POWER_LED_IDX, on ? 1 : 0);
}
