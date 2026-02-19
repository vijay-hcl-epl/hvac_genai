#ifndef CONFIGURATION_DATA_H
#define CONFIGURATION_DATA_H
#include <stdint.h>

typedef struct {
    uint16_t clamp_min;
    uint16_t clamp_max;
    uint16_t adc_min;
    uint16_t adc_max;
    uint8_t pin_uart;
    uint8_t pin_adc;
    uint8_t pin_motor;
    uint8_t pin_leds;
} configuration_t;

configuration_t* configuration_data_get(void);

#endif // CONFIGURATION_DATA_H
