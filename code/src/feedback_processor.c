#include "feedback_processor.h"
#include <stdint.h>
// ADC mock & calibration
static uint16_t calibration_table[6] = {100, 600, 1100, 1600, 2100, 2700};
#define ADC_MIN 100
#define ADC_MAX 2700
static uint16_t mock_adc_read(void) { return 1000; }

static uint16_t last_adc = 0;
static int8_t last_valid_pos = 0;

void FeedbackProcessor_Init(void) {
    last_adc = 0;
    last_valid_pos = 0;
}

// Returns position 0-5 if within bounds, else 0xFF on error
uint8_t FeedbackProcessor_GetPosition(void) {
    last_adc = mock_adc_read();
    for(uint8_t i=0; i<6; ++i) {
        uint16_t center = calibration_table[i];
        if (last_adc < center + 100 && last_adc > center - 100) {
            last_valid_pos = i;
            return i;
        }
    }
    return 0xFF;
}
