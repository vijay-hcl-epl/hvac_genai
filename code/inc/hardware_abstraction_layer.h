#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

#include <stdint.h>
typedef enum {
    HAL_STATE_IDLE,
    HAL_STATE_READING_ADC,
    HAL_STATE_MAPPING,
    HAL_STATE_PERIPHERAL_CONTROL,
    HAL_STATE_ERROR
} hal_state_t;

typedef struct {
    uint16_t adc_value;
} PeripheralADCs;

typedef struct {
    PeripheralADCs adc;
    hal_state_t state;
} HardwareAbstractionLayer;

void hal_init(HardwareAbstractionLayer* hal);
uint16_t hal_read_adc(HardwareAbstractionLayer* hal);
void hal_control_motor(HardwareAbstractionLayer* hal, int dir, int enable);
void hal_handle_error(HardwareAbstractionLayer* hal);

#endif // HARDWARE_ABSTRACTION_LAYER_H
