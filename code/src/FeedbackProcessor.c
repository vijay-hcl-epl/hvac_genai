#include "FeedbackProcessor.h"
#include "stm32f4xx_hal.h"
#include <string.h>

static FeedbackProcessor_Data_t feedback_data;
static const uint16_t position_map[CMD_MAX_POSITIONS] = {600, 1200, 2000, 2800, 3600};

void FeedbackProcessor_Init(void) {
    feedback_data.adc_value = 0U;
    feedback_data.position = 0U;
    feedback_data.valid = false;
}

void FeedbackProcessor_Update(void) {
    // Assume ADC data available in HAL_ADC_GetValue()
    uint16_t adc_raw = (uint16_t)HAL_ADC_GetValue(&hadc1);
    feedback_data.adc_value = adc_raw;
    feedback_data.valid = false;

    if ((adc_raw < FEEDBACK_ADC_MIN) || (adc_raw > FEEDBACK_ADC_MAX)) {
        feedback_data.valid = false;
        return;
    }
    for (uint8_t i = 0; i < CMD_MAX_POSITIONS; ++i) {
        uint16_t pos_val = position_map[i];
        if ((adc_raw >= pos_val - 100) && (adc_raw <= pos_val + 100)) {
            feedback_data.position = i;
            feedback_data.valid = true;
            return;
        }
    }
}

FeedbackProcessor_Data_t FeedbackProcessor_GetPosition(void) {
    return feedback_data;
}
