/* PositionFeedback.c - Implements ADC acquisition and position mapping */
#include "PositionFeedback.h"
#include "ADC.h"

static const uint16_t adcThresholds[6] = {120, 240, 360, 480, 600, 720}; // Example values

uint8_t PositionFeedback_ReadPosition(void) {
    uint16_t adcVal = 0;
    if (!ADC_Read(&adcVal))
        return 255; // Invalid
    for (uint8_t i = 0; i < 6; ++i) {
        if (adcVal < adcThresholds[i])
            return i;
    }
    return 5;
}

bool PositionFeedback_ErrorStatus(void) {
    uint16_t adcVal = 0;
    ADC_Read(&adcVal);
    return (adcVal < FEEDBACK_ADC_MIN || adcVal > FEEDBACK_ADC_MAX);
}
