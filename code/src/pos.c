#include "pos.h"

// Simulated calibration table (ADC to logical position)
static const int cal_adc_pos[6] = {100, 300, 500, 700, 900, 1100};
static int current_position = POS_POSITION_INVALID;
static bool valid_flag = false;

// Simulate ADC read
static int read_adc(void) {
    // Replace with hardware-specific ADC read
    return 700; // Example value
}

void pos_init(void) {
    current_position = POS_POSITION_INVALID;
    valid_flag = false;
}

void pos_periodic_sample(void) {
    int adc = read_adc();
    int i;
    for(i=0;i<=POS_POSITION_MAX;++i) {
        // Simple range match (+/-50 tolerance)
        if (adc >= cal_adc_pos[i]-50 && adc <= cal_adc_pos[i]+50) {
            current_position = i;
            valid_flag = true;
            return;
        }
    }
    current_position = POS_POSITION_INVALID;
    valid_flag = false;
}

bool pos_get_current_position(int *pos_value) {
    if (valid_flag) {
        if (pos_value) *pos_value = current_position;
        return true;
    }
    return false;
}

bool pos_get_valid_flag(void) {
    return valid_flag;
}
