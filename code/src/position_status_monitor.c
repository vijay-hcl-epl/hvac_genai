#include "position_status_monitor.h"
#include <stdlib.h>

static position_status_t status = { .last_position = 0, .out_of_range = false };

void position_status_init(void) {
    status.last_position = 0;
    status.out_of_range = false;
}

int position_status_get(void) {
    return status.last_position;
}

pos_status_t position_status_get_status(void) {
    return status.out_of_range ? POS_STATUS_OUT_OF_RANGE : POS_STATUS_NORMAL;
}

void position_status_periodic_task(void) {
    // Simulate reading ADC value
    int adc_sample = rand() % 120; // Simulate some out-of-range readings
    status.last_position = adc_sample;
    status.out_of_range = (adc_sample < POS_VALID_MIN || adc_sample > POS_VALID_MAX);
}
