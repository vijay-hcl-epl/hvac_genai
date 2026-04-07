#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

#include <stdint.h>
typedef enum {
    HAL_STATE_IDLE,
    HAL_STATE_ADC_SAMPLING,
    HAL_STATE_UPDATE_OUTPUT
} HALState_t;

typedef struct {
    uint16_t adc_buffer;
    uint16_t current_position;
    HALState_t state;
} HALContext_t;

void HardwareAbstractionLayer_Init(HALContext_t* ctx);
void HardwareAbstractionLayer_Task(HALContext_t* ctx);
int HardwareAbstractionLayer_SendPosition(uint16_t pos);
uint16_t HardwareAbstractionLayer_GetPosition(HALContext_t* ctx);

#endif // HARDWARE_ABSTRACTION_LAYER_H
