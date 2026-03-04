#ifndef SYSTEM_CONFIG_DATA_H
#define SYSTEM_CONFIG_DATA_H
#include <stdint.h>
#define SYSTEM_POSITION_COUNT 5

// Position ADC thresholds for mapping
struct {
    const uint8_t position_adc_thresholds[SYSTEM_POSITION_COUNT];
} SystemConfigData = {
    {52, 104, 156, 208, 255}
};

#endif // SYSTEM_CONFIG_DATA_H
