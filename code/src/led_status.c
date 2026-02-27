#include "led_status.h"
#include <string.h>

static LedStates_t led_states = {false, {false, false, false, false, false, false}};

void LEDStatus_Init(void)
{
    led_states.power_led = true;
    for(int i=0; i<6; ++i)
        led_states.pos_leds[i] = false;
}

void LEDStatus_SetPower(bool on)
{
    led_states.power_led = on;
}

void LEDStatus_SetPosition(uint8_t logical_pos)
{
    for(int i=0; i<6; ++i) led_states.pos_leds[i] = false;
    if (logical_pos < 6)
        led_states.pos_leds[logical_pos] = true;
}

void LEDStatus_ClearAll(void)
{
    led_states.power_led = false;
    for(int i=0; i<6; ++i) led_states.pos_leds[i] = false;
}
