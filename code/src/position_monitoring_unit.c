#include "position_monitoring_unit.h"
// Hardware ADC stub
static int last_adc = 0;
static int last_position = 0;
static position_status_t status = POSITION_OK;

static int adc_read(void) {
    // Hardware stub, return a test value within 0-100 by default
    return last_adc;
}

void position_monitor_init(void) {
    last_adc = 0;
    last_position = 0;
    status = POSITION_OK;
}

int get_current_position(void) {
    int adc = adc_read();
    if (adc < 0 || adc > 100) {
        status = POSITION_OOR;
        return last_position;
    }
    // Map for demonstration: 0..100 direct
    last_position = adc;
    status = POSITION_OK;
    return last_position;
}

position_status_t get_position_status(void) {
    return status;
}
