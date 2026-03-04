#ifndef SYSTEM_CONFIG_DATA_H
#define SYSTEM_CONFIG_DATA_H
#include <stdint.h>
#define NUM_POSITIONS 4
typedef struct {
    uint16_t adc_pos_thresholds[NUM_POSITIONS];
    uint8_t num_positions;
} config_data_t;
const config_data_t* CNF_Get(void);
#endif // SYSTEM_CONFIG_DATA_H
