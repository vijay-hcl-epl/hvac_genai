#include "Feedback_Processor.h"
#include "stm32f4xx_hal.h"

static uint8_t feedback_logical_position = FEEDBACK_POSITION_INVALID;
static bool feedback_valid = false;

// Example: thresholds between positions, for a 12-bit ADC (STM32F407, 0-4095)
// Adjust to match the flap positions and potentiometer scaling
const uint16_t FeedbackProcessor_ADCThresholds[FEEDBACK_POSITION_COUNT+1] = {
    0, 819, 1638, 2457, 3276, 4095
};

static ADC_HandleTypeDef hadc1;

void FeedbackProcessor_Init(void)
{
    // Init/assign hadc1 instance elsewhere (usually STM32CubeMX generated)
    feedback_logical_position = FEEDBACK_POSITION_INVALID;
    feedback_valid = false;
}

static bool is_adc_value_valid(uint16_t adc_value)
{
    return (adc_value <= 4095u);
}

static uint8_t map_adc_to_position(uint16_t adc_value)
{
    for (uint8_t i = 0; i < FEEDBACK_POSITION_COUNT; ++i) {
        if ((adc_value >= FeedbackProcessor_ADCThresholds[i]) && (adc_value < FeedbackProcessor_ADCThresholds[i+1])) {
            return i;
        }
    }
    return FEEDBACK_POSITION_INVALID;
}

void FeedbackProcessor_Update(void)
{
    uint16_t adc_value = 0;
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
        adc_value = (uint16_t)HAL_ADC_GetValue(&hadc1);
        if (is_adc_value_valid(adc_value)) {
            uint8_t pos = map_adc_to_position(adc_value);
            if (pos != FEEDBACK_POSITION_INVALID) {
                feedback_logical_position = pos;
                feedback_valid = true;
                return;
            }
        }
    }
    feedback_valid = false;
    feedback_logical_position = FEEDBACK_POSITION_INVALID;
}

bool FeedbackProcessor_GetPosition(uint8_t* position)
{
    if (feedback_valid && (feedback_logical_position != FEEDBACK_POSITION_INVALID)) {
        *position = feedback_logical_position;
        return true;
    }
    return false;
}

bool FeedbackProcessor_IsFeedbackValid(void)
{
    return feedback_valid;
}
