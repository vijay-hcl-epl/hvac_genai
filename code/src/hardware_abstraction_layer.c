#include "hardware_abstraction_layer.h"

void hal_init(HardwareAbstractionLayer* hal) {
    hal->adc.adc_value = 0;
    hal->state = HAL_STATE_IDLE;
}

uint16_t hal_read_adc(HardwareAbstractionLayer* hal) {
    // Simulate ADC read
    hal->state = HAL_STATE_READING_ADC;
    hal->adc.adc_value = 512; // fake value
    hal->state = HAL_STATE_MAPPING;
    return hal->adc.adc_value;
}

void hal_control_motor(HardwareAbstractionLayer* hal, int dir, int enable) {
    // Simulate motor control
    hal->state = HAL_STATE_PERIPHERAL_CONTROL;
}

void hal_handle_error(HardwareAbstractionLayer* hal) {
    hal->state = HAL_STATE_ERROR;
}
