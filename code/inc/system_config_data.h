#ifndef SYSTEM_CONFIG_DATA_H
#define SYSTEM_CONFIG_DATA_H
#include <stdint.h>

#define FLAP_POSITIONS 6

extern const uint16_t adc_thresholds[FLAP_POSITIONS+1];
extern const uint8_t led_pin_map[FLAP_POSITIONS];

#endif // SYSTEM_CONFIG_DATA_H
