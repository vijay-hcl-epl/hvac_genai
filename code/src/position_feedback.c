#include "position_feedback.h"
#include <stddef.h>

static PositionCalibration_t calibration = {0, 4095, {500, 1000, 2000, 2800, 3500, 4095}};
static uint16_t adc_raw_value = 0;
static uint8_t logical_position = 0xFF;
static uint8_t last_valid_position = 0;
static bool valid = false;

void PositionFeedback_Init(const PositionCalibration_t* calib)
{
    if (calib != NULL) {
        calibration = *calib;
    }
    adc_raw_value = 0;
    logical_position = 0xFF;
    last_valid_position = 0;
    valid = false;
}

void PositionFeedback_ADC_Update(uint16_t adc_value)
{
    adc_raw_value = adc_value;
    // Map ADC to logical position using thresholds
    valid = false;
    for (uint8_t i=0; i<6; ++i) {
        if (adc_raw_value <= calibration.thresholds[i]) {
            logical_position = i;
            last_valid_position = i;
            valid = true;
            return;
        }
    }
    logical_position = 0xFF;
    valid = false;
}

uint8_t PositionFeedback_GetLogicalPosition(void)
{
    if(valid) return logical_position;
    else return last_valid_position;
}

bool PositionFeedback_IsValid(void)
{
    return valid;
}
