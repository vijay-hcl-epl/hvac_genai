#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"
#include <string.h>

static HALContext_t* p_hal_ctx = 0;

void HardwareAbstractionLayer_Init(HALContext_t* ctx) {
    memset(ctx, 0, sizeof(HALContext_t));
    ctx->state = HAL_STATE_IDLE;
    p_hal_ctx = ctx;
}

int HardwareAbstractionLayer_SendPosition(uint16_t pos) {
    // Relay to driver
    return ElectricalInterfaceDriver_SetTargetPosition(pos);
}

void HardwareAbstractionLayer_Task(HALContext_t* ctx) {
    switch(ctx->state) {
        case HAL_STATE_IDLE:
            // Idle waiting for requests
            break;
        case HAL_STATE_ADC_SAMPLING:
            // Simulate ADC read, here just copy
            ctx->adc_buffer = ctx->current_position;
            ctx->state = HAL_STATE_UPDATE_OUTPUT;
            break;
        case HAL_STATE_UPDATE_OUTPUT:
            // Output position
            ElectricalInterfaceDriver_SetTargetPosition(ctx->adc_buffer);
            ctx->state = HAL_STATE_IDLE;
            break;
        default:
            ctx->state = HAL_STATE_IDLE;
            break;
    }
}

uint16_t HardwareAbstractionLayer_GetPosition(HALContext_t* ctx) {
    // Return last sampled value
    if (!ctx) return 0;
    return ctx->adc_buffer;
}
