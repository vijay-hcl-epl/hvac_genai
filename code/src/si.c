#include "si.h"
// 6 position LEDs, 1 power LED
static const int led_pins[6] = {0, 1, 2, 3, 4, 5};
static int power_led_pin = 10;
void si_init(void) {
    // Set all LEDs off
}
void si_led_update(uint8_t pos, bool power) {
    // Set all off
    // turn on pos-th LED
    // set power LED
}
