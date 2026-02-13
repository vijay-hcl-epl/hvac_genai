#include "led_stat.h"
#include "hal_gpio.h"
static const uint8_t pos_led_map[6] = {2,3,4,5,6,7};
void led_stat_init(void) { for (uint8_t i = 0; i < 6; ++i) hal_gpio_set_dir_output(pos_led_map[i]); }
void led_stat_set_led(uint8_t logical_pos) {
    for (uint8_t i = 0; i < 6; ++i)
        hal_gpio_write(pos_led_map[i], i == logical_pos ? 1 : 0);
}
