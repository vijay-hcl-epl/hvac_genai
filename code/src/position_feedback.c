#include "position_feedback.h"
#include "configuration_data.h"
#include "error_handling.h"

static uint16_t last_adc_raw = 0;

void position_feedback_init(void) {
    last_adc_raw = 0;
}

uint16_t position_feedback_get_position(void) {
    configuration_t* cfg = configuration_data_get();
    // Simulate ADC
    last_adc_raw = cfg->adc_min + ((cfg->adc_max - cfg->adc_min) / 2);
    if (!position_feedback_is_plausible()) {
        error_handling_set_error(ERR_POSITION_IMPLAUSIBLE);
    }
    return last_adc_raw;
}

bool position_feedback_is_plausible(void) {
    configuration_t* cfg = configuration_data_get();
    return (last_adc_raw >= cfg->adc_min) && (last_adc_raw <= cfg->adc_max);
}
