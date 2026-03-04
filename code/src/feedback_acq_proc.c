#include "feedback_acq_proc.h"
#include "system_config_data.h"
#include <stdint.h>

static uint8_t position = 0;

void FeedbackAcq_Trigger(void) {
    // Simulate ADC reading and map to position (demo logic)
    uint16_t adc_value = 0; // stub: should read real ADC
    for (uint8_t i = 0; i < FLAP_POSITIONS; ++i) {
        if (adc_value >= adc_thresholds[i] && adc_value < adc_thresholds[i+1]) {
            position = i;
            break;
        }
    }
}

uint8_t FeedbackAcq_GetPosition(void) {
    return position;
}
