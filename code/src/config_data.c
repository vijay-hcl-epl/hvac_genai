#include "config_data.h"
static ConfigData config = {
    .adc_thresholds = {0, 819, 1638, 2457, 3276, 4095},
    .uart_baud = 9600
};
void ConfigData_Init(void) {}
const ConfigData* ConfigData_Get(void) { return &config; }
