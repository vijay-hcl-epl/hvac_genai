#include "led_stat.h"
#include "hal_gpio.h"
static const uint8_t pos_led_map[6] = {2U, 3U, 4U, 5U, 6U, 7U};
void led_stat_init(void)
{
    uint8_t i;
    for (i = 0U; i < 6U; ++i) {
        hal_gpio_set_dir_output(pos_led_map[i]);
    }
}
void led_stat_set_led(uint8_t logical_pos)
{
    uint8_t i;
    for (i = 0U; i < 6U; ++i) {
        hal_gpio_write(pos_led_map[i], (i == logical_pos) ? 1U : 0U);
    }
}
