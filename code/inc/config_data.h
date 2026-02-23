#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <stdint.h>

#define FLAP_POS_MIN      0U
#define FLAP_POS_MAX      5U
#define ADC_NUM_POSITIONS 6U

typedef struct
{
    uint16_t adc_thresholds[ADC_NUM_POSITIONS + 1]; /* 0-6 boundaries */
    uint16_t adc_min_valid;
    uint16_t adc_max_valid;
} config_adc_map_t;

const config_adc_map_t *Config_GetADCMap(void);

#endif /* CONFIG_DATA_H */
