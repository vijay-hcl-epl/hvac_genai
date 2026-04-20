#include "config_data_store.h"

// Example configuration: 6 positions, each with ADC min/max
static const int adc_min[CONFIG_POSITIONS] = {100, 600, 1200, 1800, 2400, 3000};
static const int adc_max[CONFIG_POSITIONS] = {500, 1100, 1700, 2300, 2900, 3500};

int ConfigDataStore_GetPositionCount(void) { return CONFIG_POSITIONS; }

int ConfigDataStore_GetADCMin(int index) { return adc_min[index]; }

int ConfigDataStore_GetADCMax(int index) { return adc_max[index]; }

int Config_ADC_ReadRaw(void) {
    // TODO: Replace with real ADC read
    return 1500; // example dummy value
}

void ConfigDataStore_SetMotorDir(int dir) {
    // TODO: Replace with actual GPIO/PWM hardware control
    (void)dir;
}

void ConfigDataStore_SetMotorEnable(bool en) {
    // TODO: Replace with actual GPIO/PWM hardware control
    (void)en;
}

void ConfigDataStore_SetLED(int index, int on) {
    // TODO: Replace with actual LED GPIO control
    (void)index; (void)on;
}

void ConfigDataStore_Init(void) {}
