#include "position_feedback.h"
#include <stdint.h>
#include <stdbool.h>

// Example static calibration thresholds (4 boundaries for 5 positions)
static const uint16_t adc_thresholds[4] = {200, 500, 800, 1100}; // Replace as needed

static uint16_t latest_adc = 0;
static uint8_t last_position_index = 0;
static bool valid_position = false;
static bool fault = false;

void position_feedback_init(void)
{
    latest_adc = 0;
    last_position_index = POSITION_INDEX_INVALID;
    valid_position = false;
    fault = false;
}

void position_feedback_update(uint16_t adc_value)
{
    latest_adc = adc_value;
    // Determine position
    uint8_t pos = 0;
    fault = false;
    for (; pos < MAX_POSITION_INDEX; ++pos) {
        if (adc_value < adc_thresholds[pos]) {
            break;
        }
    }
    if (adc_value > 4095) { // assuming 12-bit ADC
        fault = true;
        last_position_index = POSITION_INDEX_INVALID;
        valid_position = false;
    } else if (pos > MAX_POSITION_INDEX) {
        fault = true;
        last_position_index = POSITION_INDEX_INVALID;
        valid_position = false;
    } else {
        last_position_index = pos;
        valid_position = true;
    }
}

position_feedback_t get_position_feedback(void)
{
    position_feedback_t fb;
    fb.adc_raw = latest_adc;
    fb.valid = valid_position;
    fb.fault = fault;
    fb.position_index = last_position_index;
    return fb;
}
