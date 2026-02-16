#include "led_indication.h"
#include <stdbool.h>
static bool power_led = false;
static int pos_led = 0;

void led_indication_init(void) {
    power_led = false;
    pos_led = 0;
}

void set_led_status(bool on) {
    power_led = on;
}

void set_led_position(int position) {
    pos_led = position;
}
