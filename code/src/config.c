#include "config.h"

static const uint16_t adc_thresholds[NUM_POSITIONS+1] = {0, 800, 1500, 2200, 2900, 4096};
static const uint8_t default_pwm_duty = 80;

bool Config_IsValidPosition(uint8_t pos) {
    return (pos < NUM_POSITIONS);
}

bool Config_MapADCToPosition(uint16_t adc, uint8_t* pos_idx) {
    for (uint8_t i = 0; i < NUM_POSITIONS; ++i) {
        if (adc >= adc_thresholds[i] && adc < adc_thresholds[i+1]) {
            *pos_idx = i;
            return true;
        }
    }
    return false;
}

uint8_t Config_GetNumPositions(void) {
    return NUM_POSITIONS;
}

uint8_t Config_GetDefaultPWMDuty(void) {
    return default_pwm_duty;
}
