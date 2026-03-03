#ifndef CALIBRATION_CONFIG_H
#define CALIBRATION_CONFIG_H
#include <stdint.h>

#define MAX_FLAP_POSITIONS 4

typedef struct {
    uint16_t adc_threshold;
    uint16_t logical_position;
} calibration_entry_t;

const calibration_entry_t* calibration_get_adc_lookup(void);
uint8_t calibration_get_num_positions(void);
uint16_t calibration_get_position_min(void);
uint16_t calibration_get_position_max(void);

#endif // CALIBRATION_CONFIG_H
