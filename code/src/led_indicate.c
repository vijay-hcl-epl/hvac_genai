#include "led_indicate.h"
#include <stdint.h>

static int led_last_position = -1;
static LED_Status_t led_status = LED_STATUS_POWER;

void LED_Init(void) {
    led_last_position = -1;
    led_status = LED_STATUS_POWER;
    // Hardware init stub
}

void LED_SetPosition(int pos) {
    // Turn off all position LEDs
    // Set only selected position LED on
    led_last_position = pos;
    led_status = LED_STATUS_POSITION;
    // Hardware interaction stub
}

void LED_SetStatus(LED_Status_t status) {
    led_status = status;
    // Hardware interaction stub (switch LED between power/position/error)
}
