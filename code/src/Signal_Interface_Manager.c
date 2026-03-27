#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

void SignalInterfaceManager_Init(SignalInterfaceManager_t *ctx) {
    ctx->queue_head = ctx->queue_tail = 0;
    ctx->state = SIG_STATE_WAIT;
    ctx->current_position = 0;
}

void SignalInterfaceManager_CommandFlap(uint8_t position) {
    // Simple queue push if space
    extern SignalInterfaceManager_t g_sig_ctx;
    uint8_t next = (g_sig_ctx.queue_tail + 1)%CMD_QUEUE_SIZE;
    if(next != g_sig_ctx.queue_head) {
        g_sig_ctx.cmd_queue[g_sig_ctx.queue_tail] = position;
        g_sig_ctx.queue_tail = next;
    }
}

void SignalInterfaceManager_Task(SignalInterfaceManager_t *ctx) {
    switch(ctx->state) {
        case SIG_STATE_WAIT:
            if(ctx->queue_head != ctx->queue_tail) {
                uint8_t pos = ctx->cmd_queue[ctx->queue_head];
                ctx->queue_head = (ctx->queue_head + 1)%CMD_QUEUE_SIZE;
                HardwareAbstractionLayer_MoveFlap(pos);
                ctx->state = SIG_STATE_PROCESSING;
            }
            break;
        case SIG_STATE_PROCESSING:
            if(HardwareAbstractionLayer_IsMoveComplete()) {
                ctx->state = SIG_STATE_COMPLETE;
            }
            break;
        case SIG_STATE_COMPLETE:
            ctx->state = SIG_STATE_WAIT;
            break;
        case SIG_STATE_ERR:
        default:
            ctx->state = SIG_STATE_WAIT;
            break;
    }
}
