#ifndef FLAP_POSITION_H
#define FLAP_POSITION_H

#include <stdint.h>

#define FLAP_POSITION_MIN 0
#define FLAP_POSITION_MAX 5

// Map ADC band to discrete flap position (0-5)
int8_t map_adc_to_flap_position(uint16_t adc_val);

#endif // FLAP_POSITION_H
