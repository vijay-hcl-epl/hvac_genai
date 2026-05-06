#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

#define FEEDBACK_ADC_CHANNEL ADC_CHANNEL_1
#define FEEDBACK_ADC_HANDLE hadc1
#define FEEDBACK_POSITIONS_COUNT 4
#define FEEDBACK_ADC_MIN 100U
#define FEEDBACK_ADC_MAX 3900U

extern ADC_HandleTypeDef FEEDBACK_ADC_HANDLE;
static const uint16_t position_adc_table[FEEDBACK_POSITIONS_COUNT] = {200, 1200, 2200, 3200};
static uint8_t curr_position = 0xFF;
static bool valid = false;

void feedback_processor_init(void) {
    curr_position = 0xFF;
    valid = false;
}

static int16_t read_adc(void) {
    HAL_ADC_Start(&FEEDBACK_ADC_HANDLE);
    if (HAL_ADC_PollForConversion(&FEEDBACK_ADC_HANDLE, 10) != HAL_OK) {
        return -1;
    }
    if ((FEEDBACK_ADC_HANDLE.Instance->DR < FEEDBACK_ADC_MIN) || (FEEDBACK_ADC_HANDLE.Instance->DR > FEEDBACK_ADC_MAX)) {
        return -1;
    }
    return (int16_t)(FEEDBACK_ADC_HANDLE.Instance->DR);
}

void feedback_processor_update(void) {
    int16_t adc_value = read_adc();
    if (adc_value < 0) {
        curr_position = 0xFF;
        valid = false;
        return;
    }
    for (uint8_t i = 0; i < FEEDBACK_POSITIONS_COUNT; ++i) {
        if (adc_value <= (int16_t)position_adc_table[i] + 100 && adc_value >= (int16_t)position_adc_table[i] - 100) {
            curr_position = i;
            valid = true;
            return;
        }
    }
    curr_position = 0xFF;
    valid = false;
}

bool feedback_processor_get_position(uint8_t *position, bool *is_valid) {
    if (position && is_valid) {
        *position = curr_position;
        *is_valid = valid;
        return true;
    }
    return false;
}
