#include "indication_led.h"
#include <stm32f4xx_hal.h>
static uint8_t led_status[6] = {0};
static uint8_t power_led = 0;
void IndicationLed_Init(void) {
    // GPIO init for LEDs
    for (uint8_t i = 0; i < 6; ++i) led_status[i] = 0;
    power_led = 0;
}
void IndicationLed_Update(uint8_t system_power, uint8_t position_idx) {
    power_led = system_power;
    for (uint8_t i = 0; i < 6; ++i) led_status[i] = 0;
    if (position_idx < 6u) led_status[position_idx] = 1;
}
