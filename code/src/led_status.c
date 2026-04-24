#include "led_status.h"
#include "hw_abstraction.h"
#define STATUS_LED_PIN 0
static const uint8_t led_map[6] = {1,2,3,4,5,6};
void led_status_init(void) {
    hw_gpio_set(STATUS_LED_PIN); // Power/status LED ON
}
void led_status_update_position(uint8_t pos) {
    for(uint8_t i=0;i<6;i++) hw_gpio_clear(led_map[i]);
    if(pos < 6) hw_gpio_set(led_map[pos]);
}
void led_status_power_on(void) {
    led_status_init();
}
