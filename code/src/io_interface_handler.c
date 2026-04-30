#include "io_interface_handler.h"

static uint16_t last_adc_value = ADC_INVALID_VALUE;

uint16_t read_adc_value(void)
{
    // TODO: Query ADC via hardware abstraction layer and validate range
    // Return ADC value, or ADC_INVALID_VALUE on error
    return last_adc_value;
}

void signal_event(void)
{
    // TODO: Process input event; raise fault flag if needed
}
