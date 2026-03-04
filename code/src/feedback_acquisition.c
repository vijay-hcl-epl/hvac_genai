#include "feedback_acquisition.h"
#include "hw_interface.h"

#define ADC_MIN      100
#define ADC_MAX      4000
#define FLAP_POSITIONS 5
static uint16_t adc_thresholds[FLAP_POSITIONS] = {500, 1250, 2000, 2750, 3500};

uint8_t feedback_acquisition_get_position(void) {
    uint16_t adc_val = adc_read();
    for (int i=0; i<FLAP_POSITIONS; ++i) {
        if (adc_val < adc_thresholds[i]) return (uint8_t)i;
    }
    return FLAP_POSITIONS-1; // max position if above all thresholds
}

void feedback_acquisition_init(void) {
}
