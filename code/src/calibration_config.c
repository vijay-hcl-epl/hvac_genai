#include "calibration_config.h"

static const calibration_entry_t calibration_table[MAX_FLAP_POSITIONS] = {
    { 1000, 0 },
    { 2000, 1 },
    { 3000, 2 },
    { 4000, 3 }
};

static const uint16_t position_min = 0;
static const uint16_t position_max = 3;
static const uint8_t num_positions = MAX_FLAP_POSITIONS;

const calibration_entry_t* calibration_get_adc_lookup(void) {
    return calibration_table;
}

uint8_t calibration_get_num_positions(void) {
    return num_positions;
}

uint16_t calibration_get_position_min(void) {
    return position_min;
}

uint16_t calibration_get_position_max(void) {
    return position_max;
}
