#include "feedback_handling.h"
#include <stdint.h>

static uint16_t feedback_adc = 0;
static int feedback_position = FEEDBACK_DISCRETE_MIN;
static bool feedback_valid = true;

// Helper: map ADC value to discrete position
static int map_adc_to_position(uint16_t adc) {
    if (adc < FEEDBACK_ADC_MIN) return FEEDBACK_DISCRETE_MIN;
    if (adc > FEEDBACK_ADC_MAX) return FEEDBACK_DISCRETE_MAX;
    // Linear mapping example
    return (int)(((adc - FEEDBACK_ADC_MIN) * (FEEDBACK_DISCRETE_MAX - FEEDBACK_DISCRETE_MIN)) /
        (FEEDBACK_ADC_MAX - FEEDBACK_ADC_MIN));
}

void FEEDBACK_Init(void) {
    feedback_adc = 0;
    feedback_position = FEEDBACK_DISCRETE_MIN;
    feedback_valid = true;
}

int FEEDBACK_ReadPosition(void) {
    return feedback_position;
}

bool FEEDBACK_IsValid(void) {
    return feedback_valid;
}

void FEEDBACK_UpdateADCValue(uint16_t adc_value) {
    feedback_adc = adc_value;
    if (feedback_adc < FEEDBACK_ADC_MIN || feedback_adc > FEEDBACK_ADC_MAX) {
        feedback_valid = false;
        feedback_position = FEEDBACK_DISCRETE_MIN;
    } else {
        feedback_valid = true;
        feedback_position = map_adc_to_position(feedback_adc);
    }
}
