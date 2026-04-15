#include "Feedback_Processor.h"
#include "stm32f4xx_hal.h"

enum {
    FEEDBACK_ADC_LOWER_BOUND = 200,
    FEEDBACK_ADC_UPPER_BOUND = 3800
};

// Example: Map ADC regions to logical positions using static lookup
// Map indices: 0,1,2,3 = Positions (must align with allowed_positions)
static const uint16_t feedback_adc_thresholds[MAX_POSITION_COMMANDS+1] = {200, 1200, 2200, 3200, 3800};

static uint16_t last_adc = 0U;
static uint8_t mapped_position = FEEDBACK_POS_INVALID;
static bool position_valid = false;

extern ADC_HandleTypeDef hadc1;

void Feedback_Processor_Init(void)
{
    last_adc = 0U;
    mapped_position = FEEDBACK_POS_INVALID;
    position_valid = false;
}

void Feedback_Processor_Update(void)
{
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        last_adc = HAL_ADC_GetValue(&hadc1);
        // validation
        if((last_adc >= FEEDBACK_ADC_LOWER_BOUND) && (last_adc < FEEDBACK_ADC_UPPER_BOUND))
        {
            // Mapping
            for(uint8_t i=0; i<MAX_POSITION_COMMANDS; ++i)
            {
                if((last_adc >= feedback_adc_thresholds[i]) && (last_adc < feedback_adc_thresholds[i+1]))
                {
                    mapped_position = allowed_positions[i];
                    position_valid = true;
                    return;
                }
            }
            position_valid = false;
            mapped_position = FEEDBACK_POS_INVALID;
        }
        else
        {
            position_valid = false;
            mapped_position = FEEDBACK_POS_INVALID;
        }
    }
    else
    {
        position_valid = false;
        mapped_position = FEEDBACK_POS_INVALID;
    }
}

uint8_t Feedback_Processor_Get_Position(void)
{
    return mapped_position;
}

bool Feedback_Processor_Is_Valid(void)
{
    return position_valid;
}
