#include "status_indicator.h"
#include "hw_abstraction.h"

#define POWER_LED_PIN   2
#define POSITION_LED_BASE_PIN 3

void StatusIndicator_Init(void)
{
    HW_GPIO_Set(POWER_LED_PIN, true);
}

void StatusIndicator_SetPowerLed(bool enable)
{
    HW_GPIO_Set(POWER_LED_PIN, enable);
}

void StatusIndicator_SetPositionLed(uint8_t position)
{
    if (position > 5u) return;
    for (uint8_t i = 0; i < 6u; ++i)
    {
        HW_GPIO_Set(POSITION_LED_BASE_PIN + i, i == position);
    }
}