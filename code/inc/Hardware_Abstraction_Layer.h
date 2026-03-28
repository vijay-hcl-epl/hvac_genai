#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H
#include <stdint.h>

typedef enum {
    HAL_STATE_IDLE = 0,
    HAL_STATE_SAMPLE_ADC,
    HAL_STATE_SET_PWM,
    HAL_STATE_SET_GPIO,
    HAL_STATE_WAIT_HW
} HardwareAbstractionLayerState;

typedef struct {
    uint8_t gpio_latch;
    uint16_t adc_reg;
    uint8_t pwm_reg;
    HardwareAbstractionLayerState state;
} HardwareAbstractionLayerContext;

void HardwareAbstractionLayer_Init(HardwareAbstractionLayerContext *ctx);
void HardwareAbstractionLayer_Process(HardwareAbstractionLayerContext *ctx);

#endif // HARDWARE_ABSTRACTION_LAYER_H
