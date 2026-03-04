#include "feedback_acq_proc.h"
#include "system_config_data.h"
#include <stdint.h>

static uint16_t last_adc = 0;
static int last_pos = -1;
static int feedback_ok = 0;

// Stub for ADC retrieval
static uint16_t read_adc(void) {
    // Replace with real ADC reading
    return 1234;
}

void feedback_acq_start(void) {
    last_adc = read_adc();
    // Map ADC to logic position via config table
    const struct pos_map_entry* map = config_get_mapping();
    int i;
    feedback_ok = 0;
    for (i=0; i<8; ++i) {
        if (last_adc <= map[i].adc_val) {
            last_pos = map[i].logic_pos;
            feedback_ok = 1;
            break;
        }
    }
}

int feedback_acq_get_position(void) {
    return (feedback_ok) ? last_pos : -1;
}

int feedback_acq_status(void) {
    return feedback_ok;
}
