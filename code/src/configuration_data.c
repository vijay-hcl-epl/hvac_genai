#include "configuration_data.h"
static configuration_t config = {
    .clamp_min = 0,
    .clamp_max = 1000,
    .adc_min = 0,
    .adc_max = 1023,
    .pin_uart = 1,
    .pin_adc = 2,
    .pin_motor = 3,
    .pin_leds = 4
};

configuration_t* configuration_data_get(void) {
    return &config;
}
