#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

// ADC value calibration table (example)
static const uint16_t adc_calib_table[FLAP_POSITION_COUNT+1] = { 0, 750, 1500, 2250, 3000, 3700, 4095 };

void feedback_processor_init(void)
{
    // ADC already initialized in main Cube config
}

int8_t feedback_get_position(void)
{
    uint32_t adc_value = 0;
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        adc_value = HAL_ADC_GetValue(&hadc1);
        for (int8_t i = 0; i < FLAP_POSITION_COUNT; i++)
        {
            if ((adc_value >= adc_calib_table[i]) && (adc_value < adc_calib_table[i+1]))
                return i;
        }
    }
    return FLAP_POSITION_INVALID;
}
