#ifndef POSITION_SENSING_AND_MONITORING_UNIT_H
#define POSITION_SENSING_AND_MONITORING_UNIT_H

#include <stdint.h>
#include <stdbool.h>

// Internal Data Design
typedef struct {
    uint16_t adc_result;
    uint16_t filtered_position;
    bool adc_valid;
} PositionSensingData_t;

void position_sensing_resp_1(PositionSensingData_t *data, uint16_t adc_sample); // Monitor flap position

#endif
