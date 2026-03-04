#include "feedback_acq_proc.h"
#include "system_config_data.h"
// Hardware-specific stubs
#define ADC_MIN  100
#define ADC_MAX  3000
static uint8_t position_index = 0;
uint16_t adc_values[6] = {200,650,1300,1800,2400,2950};
static uint16_t adc_raw_value = 0;

static uint16_t adc_read_value(void) {
    // Stub for ADC read
    return adc_raw_value;
}

void feedback_acq_proc_init(void) {
    position_index = 0;
    adc_raw_value = adc_values[0];
}

void adc_feedback_update(void) {
    adc_raw_value = adc_read_value();
    for (uint8_t i = 0; i < 6; ++i) {
        if (adc_raw_value < adc_values[i]) {
            position_index = i;
            return;
        }
    }
    position_index = 5;
}

uint8_t get_current_position(void) {
    return position_index;
}
