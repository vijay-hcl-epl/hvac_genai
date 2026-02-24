#include "position_feedback.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define NUM_FLAP_POSITIONS 6

typedef struct {
    uint16_t min_adc;
    uint16_t max_adc;
} FlapAdcRange_t;

static const FlapAdcRange_t adc_calibration_table[NUM_FLAP_POSITIONS] = {
    {   0,  600 },   // Position 0
    {  601, 1200 },   // Position 1
    { 1201, 1800 },   // Position 2
    { 1801, 2400 },   // Position 3
    { 2401, 3000 },   // Position 4
    { 3001, 4095 }    // Position 5
};

static uint16_t adc_raw_value = 0;
static uint8_t logical_position = 0;
static bool adc_valid = false;

void PositionFeedback_Init(void) {
    adc_raw_value = 0;
    logical_position = 0;
    adc_valid = false;
}

void PositionFeedback_SampleADC(void) {
    ADC_HandleTypeDef hadc1;
    hadc1.Instance = ADC1;
    HAL_ADC_Start(&hadc1);
    if(HAL_ADC_PollForConversion(&hadc1, 5) == HAL_OK) {
        adc_raw_value = HAL_ADC_GetValue(&hadc1);
    } else {
        adc_raw_value = 0xFFFF;
    }
    adc_valid = false;
    for (uint8_t i = 0; i < NUM_FLAP_POSITIONS; ++i) {
        if (adc_raw_value >= adc_calibration_table[i].min_adc && adc_raw_value <= adc_calibration_table[i].max_adc) {
            logical_position = i;
            adc_valid = true;
            break;
        }
    }
}

bool PositionFeedback_GetPosition(uint8_t *pos) {
    if (adc_valid && pos != NULL) {
        *pos = logical_position;
        return true;
    }
    return false;
}

bool PositionFeedback_IsValid(void) {
    return adc_valid;
}
