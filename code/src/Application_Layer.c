#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include <string.h>

void ApplicationLayer_Init(ApplicationLayerContext_t* ctx) {
    memset(ctx, 0, sizeof(ApplicationLayerContext_t));
    ctx->state = APP_STATE_IDLE;
}

void ApplicationLayer_Task(ApplicationLayerContext_t* ctx) {
    switch(ctx->state) {
        case APP_STATE_IDLE:
            // Wait for UART command, simulated by external call to ParseUARTInput.
            break;
        case APP_STATE_CMD_PROCESSING:
            // Command already parsed, process command
            SignalInterfaceManager_SetTargetPosition(ctx->target_flap_position);
            ctx->state = APP_STATE_INVOKE_POSITION;
            break;
        case APP_STATE_INVOKE_POSITION:
            // Wait for flap to reach commanded position
            // (Actual feedback loop left to lower layers)
            ctx->state = APP_STATE_IDLE;
            break;
        default:
            ctx->state = APP_STATE_IDLE;
            break;
    }
}

// Returns 0 for valid, -1 for invalid command
int ApplicationLayer_ParseUARTInput(ApplicationLayerContext_t* ctx, const char* uart_in) {
    if (!uart_in) return -1;
    // Expected format: "SETPOS <val>\n"
    if (strncmp(uart_in, "SETPOS ", 7) == 0) {
        int pos = atoi(&uart_in[7]);
        if (pos >= 0 && pos <= 1000) { // restrict valid position range
            ctx->target_flap_position = (uint16_t)pos;
            ctx->state = APP_STATE_CMD_PROCESSING;
            return 0;
        }
    }
    // Ignore invalid/malformed
    ctx->state = APP_STATE_IDLE;
    return -1;
}
