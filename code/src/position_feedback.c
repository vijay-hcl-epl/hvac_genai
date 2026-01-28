/**
 @file position_feedback.c
 @brief Implements ADC-based position mapping and validity check (SWE-REQ-013..015) */
#include "position_feedback.h"
#include "hw_abstraction.h"
#define NUM_FLAP_POSITIONS (6U)
#define MIN_VALID_ADC (200U)
#define MAX_VALID_ADC (3800U)

static const uint16_t position_adc_min[NUM_FLAP_POSITIONS] = { 200, 800, 1400, 2000, 2600, 3200 };
static const uint16_t position_adc_max[NUM_FLAP_POSITIONS] = { 799, 1399, 1999, 2599, 3199, 3800 };

static uint16_t adc_sample = 0U;
static uint8_t logical_position = 0U;
static bool feedback_valid = false;

void PositionFeedback_Init(void)
{
    adc_sample = 0U;
    logical_position = 0U;
    feedback_valid = false;
}

void PositionFeedback_Update(void)
{
    uint16_t sample = HW_ADC_Read();
    adc_sample = sample;
    feedback_valid = false;
    if ((sample >= MIN_VALID_ADC) && (sample <= MAX_VALID_ADC))
    {
        for (uint8_t i = 0U; i < NUM_FLAP_POSITIONS; ++i)
        {
            if ((sample >= position_adc_min[i]) && (sample <= position_adc_max[i]))
            {
                logical_position = i;
                feedback_valid = true;
                break;
            }
        }
    }
}

bool PositionFeedback_IsValid(void)
{
    return feedback_valid;
}

uint8_t PositionFeedback_GetCurrentPosition(void)
{
    return logical_position;
}
