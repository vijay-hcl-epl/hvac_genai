#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

void HardwareAbstractionLayer_Init(HardwareAbstractionLayerContext *ctx) {
    ctx->state = HAL_STATE_IDLE;
    ctx->gpio_latch = 0;
    ctx->adc_reg = 0;
    ctx->pwm_reg = 0;
}

void HardwareAbstractionLayer_Process(HardwareAbstractionLayerContext *ctx) {
    switch(ctx->state) {
        case HAL_STATE_IDLE:
            break;
        case HAL_STATE_SAMPLE_ADC:
            // Read ADC
            ctx->state = HAL_STATE_WAIT_HW;
            break;
        case HAL_STATE_SET_PWM:
            // Set PWM
            ctx->state = HAL_STATE_WAIT_HW;
            break;
        case HAL_STATE_SET_GPIO:
            // Set GPIO
            ctx->state = HAL_STATE_WAIT_HW;
            break;
        case HAL_STATE_WAIT_HW:
            ctx->state = HAL_STATE_IDLE;
            break;
        default:
            ctx->state = HAL_STATE_IDLE;
            break;
    }
}
