#include "flap_position.h"

static const uint16_t adc_band_limits[6] = { 0, 682, 1365, 2048, 2731, 3414 };

int8_t map_adc_to_flap_position(uint16_t adc_val) {
    // Map continuous ADC value to discrete positions [0-5] for the flap
    for (int8_t i = 0; i < 6; ++i) {
        if (adc_val < adc_band_limits[i]) {
            return i-1 < 0 ? 0 : i-1;
        }
    }
    return FLAP_POSITION_MAX; // Clamp to max
}
