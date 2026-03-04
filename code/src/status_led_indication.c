#include "status_led_indication.h"
// Hardware stubs for LEDs
static void set_position_led(uint8_t idx) {(void)idx;}
static void set_power_led(uint8_t on) {(void)on;}

void status_led_indication_init(void) {
    set_power_led(0);
    set_position_led(0);
}

void update_led_indication(uint8_t position_idx, uint8_t pwr_status) {
    set_power_led(pwr_status);
    set_position_led(position_idx);
}
