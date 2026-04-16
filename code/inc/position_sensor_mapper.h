#ifndef POSITION_SENSOR_MAPPER_H
#define POSITION_SENSOR_MAPPER_H

#include <stdint.h>

typedef struct {
    uint16_t pot_adc_buffer;
    uint16_t adc_range_map[6];
    uint8_t logical_position;
    uint16_t adc_min;
    uint16_t adc_max;
    uint16_t pos_thresholds[5];
} position_sensor_mapper_t;

typedef enum {
    IDLE,
    SAMPLING_ADC
} pos_sensor_state_e;

typedef enum {
    MAPPING_ADC,
    MAPPING_DONE
} pos_mapping_state_e;

typedef enum {
    VALID_RANGE,
    OUT_OF_RANGE
} pos_range_state_e;

void position_sensor_mapper_resp_1(position_sensor_mapper_t *ctx);
void position_sensor_mapper_resp_2(position_sensor_mapper_t *ctx);
void position_sensor_mapper_resp_3(position_sensor_mapper_t *ctx);
void position_sensor_mapper_resp_4(position_sensor_mapper_t *ctx);

#endif
