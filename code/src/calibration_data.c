#include "calibration_data.h"
#define NUM_POSITIONS 6
static const uint16_t pos_thresholds[NUM_POSITIONS+1] = {0, 700, 1400, 2100, 2800, 3500, 4096};
uint8_t MapAdcToPosition(uint16_t adc_value) {
    for (int i = 0; i < NUM_POSITIONS; ++i) {
        if (adc_value >= pos_thresholds[i] && adc_value < pos_thresholds[i+1])
            return i;
    }
    return 0xFF;
}
void CalibrationData_Init(void) {}
