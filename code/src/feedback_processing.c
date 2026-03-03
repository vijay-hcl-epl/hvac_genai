#include "feedback_processing.h"
#include "calibration_config.h"
#include "error_safety_monitor.h"
#include <stdint.h>

static uint16_t last_adc_value = 0;
static uint16_t computed_position = 0;

static uint16_t read_adc(void) {
    // Platform-specific ADC read
    return 0;
}

static uint16_t map_adc_to_position(uint16_t adc_value) {
    // Example: use calibration thresholds
    const calibration_entry_t *table = calibration_get_adc_lookup();
    uint8_t n = calibration_get_num_positions();
    for (uint8_t i = 0; i < n; ++i) {
        if (adc_value <= table[i].adc_threshold) {
            return table[i].logical_position;
        }
    }
    // If out-of-range
    error_safety_monitor_set_error();
    return 0;
}

void feedback_processing_init(void) {
    last_adc_value = 0;
    computed_position = 0;
}

uint16_t feedback_processing_get_position(void) {
    last_adc_value = read_adc();
    computed_position = map_adc_to_position(last_adc_value);
    return computed_position;
}
