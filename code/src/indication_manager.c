/**
 @file indication_manager.c
 @brief Implementation of status and position LED indication (SWE-REQ-016..017) */
#include "indication_manager.h"
#include "hw_abstraction.h"
#define NUM_POSITION_LEDS (6U)
#define POWER_LED_INDEX (6U)

void IndicationManager_Init(void)
{
    for (uint8_t i = 0U; i < NUM_POSITION_LEDS; ++i)
    {
        HW_LED_Set(i, false);
    }
    HW_LED_Set(POWER_LED_INDEX, false);
}

void IndicationManager_Update(bool system_power_on, uint8_t logical_position, bool pos_valid)
{
    HW_LED_Set(POWER_LED_INDEX, system_power_on);
    for (uint8_t i = 0U; i < NUM_POSITION_LEDS; ++i)
    {
        if (pos_valid && (logical_position == i))
        {
            HW_LED_Set(i, true);
        }
        else
        {
            HW_LED_Set(i, false);
        }
    }
}
