#include "static_config.h"
const uint16_t adc_thresholds[6][2] = {
    {0U, 1000U}, {1001U, 2000U}, {2001U, 3000U}, {3001U, 3500U}, {3501U, 4000U}, {4001U, 4095U}
};
const uint8_t position_map[6] = {0U,1U,2U,3U,4U,5U};
uint16_t StaticConfig_GetThresholdMin(uint8_t idx) {
    if (idx < 6U) { return adc_thresholds[idx][0]; }
    return 0U;
}
uint16_t StaticConfig_GetThresholdMax(uint8_t idx) {
    if (idx < 6U) { return adc_thresholds[idx][1]; }
    return 4095U;
}
uint8_t StaticConfig_GetPositionMap(uint8_t idx) {
    if (idx < 6U) { return position_map[idx]; }
    return 0xFFU;
}
void StaticConfig_Init(void) {}
