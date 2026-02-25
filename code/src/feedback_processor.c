#include "feedback_processor.h"
#include "hw_abstraction.h"
#include <stdint.h>
#include <stdbool.h>

// Example: thresholds for 0-5 positions
static const uint16_t adc_thresh[6] = {300, 900, 1500, 2100, 2700, 3300};

static uint8_t current_position = 0u;
static bool position_valid = false;

void FeedbackProcessor_Init(void)
{
    current_position = 0u;
    position_valid = false;
}

void FeedbackProcessor_SampleAndUpdate(void)
{
    uint16_t adc_value = HW_ADC_Read();
    position_valid = false;
    for (uint8_t i = 0; i < 6u; ++i)
    {
        if (adc_value < adc_thresh[i])
        {
            current_position = i;
            position_valid = true;
            break;
        }
    }
}

uint8_t FeedbackProcessor_GetCurrentPosition(void)
{
    return current_position;
}

bool FeedbackProcessor_IsPositionValid(void)
{
    return position_valid;
}