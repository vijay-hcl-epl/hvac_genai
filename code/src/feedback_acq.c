#include "feedback_acq.h"
#include <stddef.h>

// ADC mapping constants [purely per SW LLD table, thresholding parameters TBD]
#define ADC_CH_FLAP_POT 0 // [TBD — Not found in datasheet: which P2.x, analog channel assignment]
static const struct {
    uint16_t min, max;
} adc_position_ranges[FLAP_POS_MAX+1] = {
    {0, 1023},   // 0 (TBD)
    {1024, 2047},// 1 (TBD)
    {2048, 3071},// 2 (TBD)
    {3072, 4095},// 3 (TBD)
    {4096, 5120},// 4 (TBD)
    {5121, 6143} // 5 (TBD)
};

extern uint16_t adc_read(uint8_t ch); // Provided by MCU lib; not implemented here

uint8_t get_flap_position(void) {
    uint16_t adc_val = adc_read(ADC_CH_FLAP_POT); // Use correct HW channel for P2.x
    for (uint8_t i = 0; i <= FLAP_POS_MAX; ++i) {
        if (adc_val >= adc_position_ranges[i].min && adc_val <= adc_position_ranges[i].max)
            return i;
    }
    return FLAP_POS_INVALID;
}
