#ifndef STATIC_CONFIG_H
#define STATIC_CONFIG_H
#include <stdint.h>
const uint16_t adc_thresholds[6][2];
const uint8_t position_map[6];
uint16_t StaticConfig_GetThresholdMin(uint8_t idx);
uint16_t StaticConfig_GetThresholdMax(uint8_t idx);
uint8_t StaticConfig_GetPositionMap(uint8_t idx);
void StaticConfig_Init(void);
#endif /* STATIC_CONFIG_H */
