#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"

// Example UART receive stub
static int UART_Read(char *buffer, int maxlen);
static void UART_ClearBuffer(char *buffer, int len);

void ApplicationLayer_Init(ApplicationLayer_t *ctx) {
    ctx->cmd_length = 0;
    ctx->state = STATE_IDLE;
    ctx->target_flap_position = 0;
    UART_ClearBuffer(ctx->uart_rx_buffer, UART_CMD_BUFFER_SIZE);
}

void ApplicationLayer_Task(ApplicationLayer_t *ctx) {
    switch(ctx->state) {
        case STATE_IDLE:
            ctx->cmd_length = UART_Read(ctx->uart_rx_buffer, UART_CMD_BUFFER_SIZE);
            if(ctx->cmd_length > 0) {
                ctx->state = STATE_CMD_RECV;
            }
            break;
        case STATE_CMD_RECV:
            // Example: expect a single-digit ASCII position (0-5)
            if(ctx->cmd_length == 1 && ctx->uart_rx_buffer[0] >= '0' && ctx->uart_rx_buffer[0] <= '5') {
                ctx->target_flap_position = ctx->uart_rx_buffer[0] - '0';
                ctx->state = STATE_FLAP_SETPOINT;
            } else {
                ctx->state = STATE_ERROR;
            }
            break;
        case STATE_FLAP_SETPOINT:
            SignalInterfaceManager_CommandFlap(ctx->target_flap_position);
            ctx->state = STATE_IDLE;
            break;
        case STATE_ERROR:
        default:
            // Ignore invalid
            ctx->state = STATE_IDLE;
            break;
    }
}

static int UART_Read(char *buffer, int maxlen) {
    // HW-specific code – stub for integration
    // Return 0 for no data received
    return 0;
}
static void UART_ClearBuffer(char *buffer, int len) {
    for(int i=0;i<len;i++) buffer[i] = 0;
}
