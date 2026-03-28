#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

void SignalInterfaceManager_Init(SignalInterfaceManagerContext *ctx) {
    ctx->state = SIM_STATE_IDLE;
    ctx->led_state = 0;
    for (int i = 0; i < 8; ++i) ctx->uart_buffer[i] = 0;
}

void SignalInterfaceManager_Process(SignalInterfaceManagerContext *ctx) {
    switch(ctx->state) {
        case SIM_STATE_IDLE:
            // Wait for signal
            break;
        case SIM_STATE_ROUTE_UART:
            // Route UART command
            ctx->state = SIM_STATE_WAIT_LOWER;
            break;
        case SIM_STATE_ROUTE_LED:
            // Route LED signal
            ctx->state = SIM_STATE_WAIT_LOWER;
            break;
        case SIM_STATE_WAIT_UPPER:
            // Wait for handshake
            ctx->state = SIM_STATE_IDLE;
            break;
        case SIM_STATE_WAIT_LOWER:
            // Handshake with lower unit
            ctx->state = SIM_STATE_IDLE;
            break;
        default:
            ctx->state = SIM_STATE_IDLE;
            break;
    }
}
