#include "Electrical_Interface_Driver.h"

void ElectricalInterfaceDriver_Init(ElectricalInterfaceDriverContext *ctx) {
    ctx->state = EID_STATE_IDLE;
    ctx->output_latch = 0;
    ctx->adc_sample = 0;
    ctx->pwm_level = 0;
}

void ElectricalInterfaceDriver_Process(ElectricalInterfaceDriverContext *ctx) {
    switch(ctx->state) {
        case EID_STATE_IDLE:
            break;
        case EID_STATE_ACTUATE:
            // Actuate hardware
            ctx->state = EID_STATE_HOLD;
            break;
        case EID_STATE_SAMPLE:
            // Sample ADC
            ctx->state = EID_STATE_HOLD;
            break;
        case EID_STATE_HOLD:
            ctx->state = EID_STATE_IDLE;
            break;
        default:
            ctx->state = EID_STATE_IDLE;
            break;
    }
}
