#include "static_config.h"
const uint16_t adc_thresholds[6][2] = {
    {0, 1000}, {1001, 2000}, {2001, 3000}, {3001, 3500}, {3501, 4000}, {4001, 4095}
};
const uint8_t position_map[6] = {0,1,2,3,4,5};
uint16_t StaticConfig_GetThresholdMin(uint8_t idx) {
    if (idx < 6u) return adc_thresholds[idx][0];
    return 0;
}
uint16_t StaticConfig_GetThresholdMax(uint8_t idx) {
    if (idx < 6u) return adc_thresholds[idx][1];
    return 4095;
}
uint8_t StaticConfig_GetPositionMap(uint8_t idx) {
    if (idx < 6u) return position_map[idx];
    return 0xFF;
}
void StaticConfig_Init(void) {}
