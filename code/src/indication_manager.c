#include "indication_manager.h"
#include <stdint.h>
#include <stdbool.h>
#define N_POS_LEDS 6
// Stubs: assign proper GPIOs per board schematic
static const uint8_t pos_led_pins[N_POS_LEDS] = {0,1,2,3,4,5};
static const uint8_t power_led_pin = 10;
static uint8_t last_shown_pos = 0xFF;

static void led_on(uint8_t pin)  { (void)pin; /* Write to GPIO HIGH*/ }
static void led_off(uint8_t pin) { (void)pin; /* Write to GPIO LOW*/ }

void indication_update(uint8_t current_pos, bool valid) {
    uint8_t i;
    if (!valid) {
        for (i = 0U; i < N_POS_LEDS; ++i) {
            led_off(pos_led_pins[i]);
        }
        led_on(power_led_pin);
        last_shown_pos = 0xFF;
        return;
    }
    if (current_pos != last_shown_pos) {
        for (i = 0U; i < N_POS_LEDS; ++i) {
            if (i == current_pos) {
                led_on(pos_led_pins[i]);
            } else {
                led_off(pos_led_pins[i]);
            }
        }
        last_shown_pos = current_pos;
    }
    led_on(power_led_pin);
}
