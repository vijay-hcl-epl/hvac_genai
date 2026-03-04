#include "feedback_acq_proc.h"
#include "system_config_data.h"
#include <stdint.h>
static uint8_t adc_value = 0;
static uint8_t mapped_position = 0;

void FeedbackAcq_Trigger(void) {
    // Stub: Simulate ADC read (replace in real code)
    adc_value =  (uint8_t)(rand() % 256); // e.g., fake ADC 8-bit
    // map ADC to position
    for (uint8_t i=0;i<SYSTEM_POSITION_COUNT;i++) {
        if (adc_value < SystemConfigData.position_adc_thresholds[i]) {
            mapped_position = i;
            break;
        }
    }
}

uint8_t FeedbackAcq_GetPosition(void) {
    return mapped_position;
}
