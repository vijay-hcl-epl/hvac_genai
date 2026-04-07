#include "Electrical_Interface_Driver.h"
#include <string.h>

static ElectricalDriverContext_t* p_drv_ctx = 0;
static uint16_t g_position_target = 0;

void ElectricalInterfaceDriver_Init(ElectricalDriverContext_t* ctx) {
    memset(ctx, 0, sizeof(ElectricalDriverContext_t));
    ctx->state = EDRV_STATE_IDLE;
    p_drv_ctx = ctx;
}

int ElectricalInterfaceDriver_SetTargetPosition(uint16_t pos) {
    g_position_target = pos;
    if (p_drv_ctx) {
        p_drv_ctx->motor_enable = 1;
        p_drv_ctx->state = EDRV_STATE_DRIVE;
        return 0;
    }
    return -1;
}

void ElectricalInterfaceDriver_Task(ElectricalDriverContext_t* ctx) {
    switch(ctx->state) {
        case EDRV_STATE_IDLE:
            // standby
            break;
        case EDRV_STATE_DRIVE:
            // Simulate driving to target: set output, LED
            // When done, disable motor
            ctx->motor_enable = 0;
            ctx->state = EDRV_STATE_REST;
            break;
        case EDRV_STATE_REST:
            // Wait here, return to idle after some logic (not invented)
            ctx->state = EDRV_STATE_IDLE;
            break;
        default:
            ctx->state = EDRV_STATE_IDLE;
            break;
    }
}
