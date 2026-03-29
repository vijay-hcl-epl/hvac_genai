#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

#include <stdint.h>

typedef enum {
    HAL_STATE_IDLE,
    HAL_STATE_ACTUATE,
    HAL_STATE_FEEDBACK
} HardwareAbstraction_State_e;

typedef struct {
    uint8_t currentState;
    uint16_t adcValue;
    uint8_t motorActive;
} HardwareAbstraction_Data_t;

void HardwareAbstraction_Init(HardwareAbstraction_Data_t *hal);
void HardwareAbstraction_Actuate(HardwareAbstraction_Data_t *hal, uint16_t position);
void HardwareAbstraction_UpdateFeedback(HardwareAbstraction_Data_t *hal);

#endif // HARDWARE_ABSTRACTION_LAYER_H
