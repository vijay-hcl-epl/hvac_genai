#include "StatusIndicator.h"

#define NUM_LEDS 5
static uint8_t led_states[NUM_LEDS] = {0};
static bool power_led_on = false;

// Hardware abstraction: To be replaced with GPIO, etc
typedef void (*SetLedFn)(uint8_t idx, bool on);
static SetLedFn set_led_fn = 0;

void StatusIndicator_Update(enum FlapPosition pos, bool powerOn) {
    power_led_on = powerOn;
    if(set_led_fn == 0) return;
    for(uint8_t i = 0; i < NUM_LEDS; ++i) set_led_fn(i, false);
    if(pos > FLAP_POS_INVALID && pos < FLAP_POS_MAX) {
        set_led_fn((uint8_t)pos, true);
    }
}

void StatusIndicator_SetLedFunction(SetLedFn fn) {
    set_led_fn = fn;
}
