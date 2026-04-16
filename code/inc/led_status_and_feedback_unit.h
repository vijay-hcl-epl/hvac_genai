#ifndef LED_STATUS_AND_FEEDBACK_UNIT_H
#define LED_STATUS_AND_FEEDBACK_UNIT_H

#include <stdint.h>
#include <stdbool.h>

// Internal Data Design
#define MAX_POSITION_LEDS 10
typedef struct {
    bool power_led;
    bool position_leds[MAX_POSITION_LEDS];
} LedStatusData_t;

void led_status_resp_1(LedStatusData_t *data, bool power_on); // Indicate power
void led_status_resp_2(LedStatusData_t *data, uint8_t position, bool valid); // Indicate flap position

#endif
