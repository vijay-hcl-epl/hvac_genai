#include "config_data.h"

static const ConfigData_t config = {
    .adc_thresholds = {800, 1200, 1600, 2000, 2400, 2800},
    .baudrate = 115200,
    .uart_channel = 1
};

const ConfigData_t* ConfigData_Get(void) {
    return &config;
}
