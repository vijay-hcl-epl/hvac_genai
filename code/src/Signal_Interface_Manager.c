#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include <string.h>

static SignalInterfaceContext_t* p_ctx = 0;

void SignalInterfaceManager_Init(SignalInterfaceContext_t* ctx) {
    memset(ctx, 0, sizeof(SignalInterfaceContext_t));
    ctx->state = SIGIF_STATE_IDLE;
    p_ctx = ctx;
}

// Simulate external call to set position
void SignalInterfaceManager_SetTargetPosition(uint16_t target_pos) {
    if (p_ctx) {
        p_ctx->target_position_input = target_pos;
        p_ctx->state = SIGIF_STATE_CONVERTING;
    }
}

void SignalInterfaceManager_Task(SignalInterfaceContext_t* ctx) {
    switch(ctx->state) {
        case SIGIF_STATE_IDLE: /* wait for input */ break;
        case SIGIF_STATE_CONVERTING:
            // Simple scale (identity); extend for actual scaling rules as needed
            ctx->digital_position = ctx->target_position_input;
            ctx->state = SIGIF_STATE_FORWARD;
            break;
        case SIGIF_STATE_FORWARD:
            if(HardwareAbstractionLayer_SendPosition(ctx->digital_position) == 0)
                ctx->state = SIGIF_STATE_IDLE;
            else // on error
                ctx->state = SIGIF_STATE_IDLE;
            break;
        default:
            ctx->state = SIGIF_STATE_IDLE;
            break;
    }
}
