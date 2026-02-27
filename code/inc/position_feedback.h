#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H

#include <stdint.h>
#include <stdbool.h>

#define ADC_POSITION_THRESHOLDS {200, 500, 800, 1100} // example values; adjust per calibration
#define POSITION_INDEX_INVALID 0xFF
#define MAX_POSITION_INDEX 4

// Structure for position feedback
typedef struct {
    uint8_t position_index;
    bool valid;
    bool fault;
    uint16_t adc_raw;
} position_feedback_t;

// Initialize feedback processing
void position_feedback_init(void);
// Acquire and process feedback
position_feedback_t get_position_feedback(void);
// For integration: call when new ADC sample available
void position_feedback_update(uint16_t adc_value);

#endif // POSITION_FEEDBACK_H
