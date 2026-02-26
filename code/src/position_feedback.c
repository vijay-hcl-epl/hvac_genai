#include "position_feedback.h"
#include "hal.h"

#define NUM_FLAP_POSITIONS 6
static uint16_t position_lookup_table[NUM_FLAP_POSITIONS] = {200, 600, 1000, 1400, 1800, 2200}; // Example calibration
static int last_position = -1;
static bool position_valid_flag = false;
static bool error_flag = false;

void position_feedback_init(void) {
    last_position = -1;
    position_valid_flag = false;
    error_flag = false;
}

// Simulate ADC read and position lookup
void position_feedback_update(void) {
    uint16_t adc_value = hal_adc_read();
    bool found = false;
    for(int i = 0; i < NUM_FLAP_POSITIONS; i++) {
        if(adc_value < position_lookup_table[i] + 100 && adc_value > position_lookup_table[i] - 100) {
            last_position = i;
            position_valid_flag = true;
            error_flag = false;
            found = true;
            break;
        }
    }
    if(!found) {
        position_valid_flag = false;
        error_flag = true;
    }
}

int position_feedback_get_position(void) {
    if(position_valid_flag) return last_position;
    return -1;
}

bool position_feedback_is_valid(void) {
    return position_valid_flag;
}
