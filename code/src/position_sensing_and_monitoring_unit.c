#include "position_sensing_and_monitoring_unit.h"

// Continuously monitor flap position using potentiometer feedback via ADC
void position_sensing_resp_1(PositionSensingData_t *data, uint16_t adc_sample) {
    data->adc_result = adc_sample;
    // Assume direct store; filtering not detailed in LLD
    data->filtered_position = adc_sample;
    if (adc_sample < 0 || adc_sample > 1023) {
        data->adc_valid = false;
    } else {
        data->adc_valid = true;
    }
}
