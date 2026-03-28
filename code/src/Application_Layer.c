#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"

void ApplicationLayer_Init(ApplicationLayerContext *ctx) {
    ctx->state = APP_STATE_IDLE;
    ctx->target_position = 0;
    for (int i = 0; i < 8; ++i) ctx->command_buffer[i] = 0;
}

void ApplicationLayer_Process(ApplicationLayerContext *ctx) {
    switch(ctx->state) {
        case APP_STATE_IDLE:
            // Wait for command received via interface
            break;
        case APP_STATE_RECEIVE_COMMAND:
            // Receive UART command
            ctx->state = APP_STATE_PARSE_COMMAND;
            break;
        case APP_STATE_PARSE_COMMAND:
            // Parse, validate
            if(/*valid*/) {
                ctx->target_position = ctx->command_buffer[0]; // example
                ctx->state = APP_STATE_DISPATCH_REQUEST;
            } else {
                ctx->state = APP_STATE_IDLE;
            }
            break;
        case APP_STATE_DISPATCH_REQUEST:
            // Send to lower abstraction (Signal_Interface_Manager)
            ctx->state = APP_STATE_WAIT_CONFIRM;
            break;
        case APP_STATE_WAIT_CONFIRM:
            // Wait for lower confirmation
            ctx->state = APP_STATE_IDLE;
            break;
        default:
            ctx->state = APP_STATE_IDLE;
            break;
    }
}
