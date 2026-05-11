#include "position_feedback.h"

#define NUM_POSITIONS 5
#define ADC_MAX 1023
static const uint16_t adc_ranges[NUM_POSITIONS+1] = {0, 200, 400, 600, 800, 1024}; // Example

static feedback_cb_t feedback_cb = 0;

void position_feedback_init(feedback_cb_t cb)
{
    feedback_cb = cb;
}

void position_feedback_update(void)
{
    // Simulate ADC read; replace with HW
    uint16_t adc_val = 0;
    uint8_t logical_pos = 0xFF;
    bool in_range = false;
    // Example: acquire adc_val from hardware
    for (uint8_t i=0; i<NUM_POSITIONS; ++i) {
        if (adc_val >= adc_ranges[i] && adc_val < adc_ranges[i+1]) {
            logical_pos = i;
            in_range = true;
            break;
        }
    }
    if (feedback_cb) feedback_cb(logical_pos, in_range);
}
