#include "position_feedback_reader.h"
#include <stdint.h>
#include <stdbool.h>

#define ADC_CHANNEL_FLAP 0
#define FILTER_DEPTH 8
#define POSITION_MIN 0
#define POSITION_MAX 3

static uint16_t adc_samples[FILTER_DEPTH];
static uint32_t adc_sum = 0;
static uint8_t adc_idx = 0;

// Dummy ADC abstraction for platform independence
static uint16_t adc_read(uint8_t channel) {
    (void)channel;
    // Simulate a return value [0, 3]
    return 0;
}

void position_feedback_reader_init(void) {
    for (uint8_t i = 0; i < FILTER_DEPTH; ++i) {
        adc_samples[i] = 0;
    }
    adc_sum = 0;
    adc_idx = 0;
}

uint16_t get_position(void) {
    uint16_t new_sample = adc_read(ADC_CHANNEL_FLAP);
    adc_sum -= adc_samples[adc_idx];
    adc_samples[adc_idx] = new_sample;
    adc_sum += adc_samples[adc_idx];
    adc_idx = (adc_idx + 1) % FILTER_DEPTH;
    uint16_t avg = (uint16_t)(adc_sum / FILTER_DEPTH);
    // Clamp to min...max
    if (avg < POSITION_MIN) avg = POSITION_MIN;
    if (avg > POSITION_MAX) avg = POSITION_MAX;
    return avg;
}

bool is_position_valid(uint16_t position) {
    return (position >= POSITION_MIN && position <= POSITION_MAX);
}
