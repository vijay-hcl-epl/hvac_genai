#include "position_acquisition.h"

#define ADC_CHANNEL_FLAP 0
#define ADC_MIN 0
#define ADC_MAX 4095
#define FLAP_ANGLE_MIN 0
#define FLAP_ANGLE_MAX 100

static int raw_adc_value = 0;
static int position_angle = 0;

static int ReadADCChannel(uint8_t channel_id) {
    // TODO: Implement ADC driver interface
    // Placeholder implementation
    return ADC_MIN;
}

void UpdatePosition(void) {
    raw_adc_value = ReadADCChannel(ADC_CHANNEL_FLAP);
    // Validate raw_adc_value
    if (raw_adc_value < ADC_MIN || raw_adc_value > ADC_MAX) {
        // Error: out of bounds, clamp to min
        raw_adc_value = ADC_MIN;
    }
    // Linear conversion
    position_angle = (raw_adc_value * (FLAP_ANGLE_MAX - FLAP_ANGLE_MIN)) / ADC_MAX;
}

int GetCurrentPosition(void) {
    return position_angle;
}
