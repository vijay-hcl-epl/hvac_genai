#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

#include <stdint.h>
#include <stdbool.h>

// State Machine
typedef enum {
    HAL_INIT,
    HAL_READY,
    HAL_OPERATIONAL
} HalState_t;

// Abstraction for hardware devices
typedef struct {
    uint16_t adc_value;
    uint8_t gpio_state;
    uint8_t led_status;
    HalState_t state;
} HardwareAbstractionLayer_Data_t;

void HardwareAbstractionLayer_Init(HardwareAbstractionLayer_Data_t *data);
void HardwareAbstractionLayer_Periodic(HardwareAbstractionLayer_Data_t *data);
void HardwareAbstractionLayer_ReceiveCommand(uint8_t cmd);

#endif // HARDWARE_ABSTRACTION_LAYER_H
