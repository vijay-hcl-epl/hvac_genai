#include "system_config_data.h"
const uint16_t adc_ranges[6] = {200,650,1300,1800,2400,2950};
static uint8_t system_power_status = 1; // Always powered in this stub
uint8_t get_system_power_status(void) {
    return system_power_status;
}
