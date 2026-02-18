#include "feedback_acquisition.h"

// ADC threshold mapping (static/const), as per LLD; use external configuration if Infineon datasheet provides ranges
static const struct { uint16_t lo; uint16_t hi; } adc_thresholds[6] = {
    {0, 683},   // 0: 0..683
    {684, 1365},// 1
    {1366, 2047},// 2
    {2048, 2730},// 3
    {2731, 3413},// 4
    {3414, 4095}// 5: 3414..4095
};

// Simulated ADC raw read
static uint16_t adc_raw_value = 0; // [TBD - Infineon ADC read specifics]

int get_current_position(void) {
    // TODO: Read adc_raw_value from Infineon TLE9851QXW ADC register
    for (int i = POSITION_MIN; i <= POSITION_MAX; ++i) {
        if (adc_raw_value >= adc_thresholds[i].lo && adc_raw_value <= adc_thresholds[i].hi) {
            return i;
        }
    }
    return POSITION_INVALID;
}
