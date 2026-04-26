#include "position_sensing_feedback.h"
#include <stdint.h>

#define LOGIC_POSITIONS 5
// Example ADC boundaries (modify/configure per system)
static const unsigned int adc_min[LOGIC_POSITIONS] = {100, 300, 500, 700, 900};
static const unsigned int adc_max[LOGIC_POSITIONS] = {299, 499, 699, 899, 1023};
static unsigned int last_position = 0; // Logical
static uint16_t last_adc = 0;

void position_sensing_init(void) {
    last_position = 0;
    last_adc = 0;
}

void update_position_feedback(void) {
    last_adc = get_adc_sample();
    for (unsigned int i = 0; i < LOGIC_POSITIONS; ++i) {
        if (last_adc >= adc_min[i] && last_adc <= adc_max[i]) {
            last_position = i;
            return;
        }
    }
    // Out of bounds: -1 (not a valid logical position)
    last_position = (unsigned int)-1;
}

unsigned int get_current_logical_position(void) {
    update_position_feedback();
    return last_position;
}

bool adc_in_bounds(unsigned int adc_val) {
    for (unsigned int i = 0; i < LOGIC_POSITIONS; ++i) {
        if (adc_val >= adc_min[i] && adc_val <= adc_max[i]) {
            return true;
        }
    }
    return false;
}

__attribute__((weak)) uint16_t get_adc_sample(void) {
    // Replace this with actual ADC code
    return 512;
}
