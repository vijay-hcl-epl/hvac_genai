#include "indication_led.h"
#include <stm32f4xx_hal.h>
static uint8_t led_status[6] = {0U};
static uint8_t power_led = 0U;
void IndicationLed_Init(void) {
    /* GPIO init for LEDs */
    for (uint8_t i = 0U; i < 6U; ++i) { led_status[i] = 0U; }
    power_led = 0U;
}
void IndicationLed_Update(uint8_t system_power, uint8_t position_idx) {
    power_led = system_power;
    for (uint8_t i = 0U; i < 6U; ++i) { led_status[i] = 0U; }
    if (position_idx < 6U) { led_status[position_idx] = 1U; }
}
