#include "uart_handler.h"
#include "command_dispatcher.h"

static uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static size_t rx_idx = 0;
static UartHandlerState_t state = UART_STATE_IDLE;

#define CMD_START_DELIM    0xAA
#define CMD_END_DELIM      0x55

void UART_Handler_Init(void) {
    rx_idx = 0;
    state = UART_STATE_IDLE;
}

void UART_Handler_RxISR(uint8_t byte) {
    switch (state) {
        case UART_STATE_IDLE:
            if (byte == CMD_START_DELIM) {
                rx_idx = 0;
                state = UART_STATE_RECEIVING;
            }
            break;
        case UART_STATE_RECEIVING:
            if (rx_idx < UART_RX_BUFFER_SIZE) {
                rx_buffer[rx_idx++] = byte;
                if (byte == CMD_END_DELIM) {
                    state = UART_STATE_FRAME_COMPLETE;
                }
            } else {
                state = UART_STATE_ERROR;
            }
            break;
        case UART_STATE_FRAME_COMPLETE:
        case UART_STATE_ERROR:
            // Ignore until processed/reset
            break;
        default:
            state = UART_STATE_ERROR;
            break;
    }
}

int UART_Handler_GetParsedCommand(uint8_t* buf, size_t* len) {
    if (state == UART_STATE_FRAME_COMPLETE && rx_idx > 2) {
        size_t out_len = rx_idx - 2;
        for (size_t i = 0; i < out_len; ++i) {
            buf[i] = rx_buffer[i+1];
        }
        *len = out_len;
        // Forward to Command Dispatcher
        CommandDispatcher_ReceiveCommand(buf, out_len);
        rx_idx = 0;
        state = UART_STATE_IDLE;
        return 1;
    } else if (state == UART_STATE_ERROR) {
        // Reset on error
        rx_idx = 0;
        state = UART_STATE_IDLE;
        return -1;
    }
    return 0;
}
