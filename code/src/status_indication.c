#include "status_indication.h"
#include "hw_interface.h"

#define POSITION_LED_START  0
#define NUM_POSITION_LEDS   5
static uint8_t current_led = 0xFF;
static bool    error_state = false;

void status_indication_init(void) {}

void status_indication_set_position(uint8_t pos) {
    // Switch LEDs
    for (int i=0; i<NUM_POSITION_LEDS; ++i)
        gpio_clear(POSITION_LED_START+i);
    gpio_set(POSITION_LED_START+pos);
    current_led = pos;
    error_state = false;
}
void status_indication_set_error(bool err) {
    error_state = err;
    // Light a dedicated error LED; placeholder: gpio_set(9);
    if (err) gpio_set(9); else gpio_clear(9);
}
