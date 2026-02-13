#include "led_stat.h"
#include "hal_gpio.h"
static const uint8_t pos_led_map[6] = {2,3,4,5,6,7};
void led_stat_init(void) {
    uint8_t i;
    for (i = 0; i < 6; ++i) { /* MISRA: Rule 17.8 – Minimize scope, declare iterator at function top */
        hal_gpio_set_dir_output(pos_led_map[i]);
    }
}
void led_stat_set_led(uint8_t logical_pos) {
    uint8_t i;
    for (i = 0; i < 6; ++i) {
        hal_gpio_write(pos_led_map[i], (i == logical_pos) ? 1 : 0);
    }
}
