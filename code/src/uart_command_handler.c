#include "uart_command_handler.h"
#include "flap_control_logic.h"

static char rx_buf[UART_RX_BUF_LEN];
static int rx_index = 0;
static bool cmd_valid = false;
static int cmd_value = 0;

void UART_CommandHandler_Init(void) {
    rx_index = 0;
    cmd_valid = false;
    cmd_value = -1;
}

static void reset_buf(void) {
    rx_index = 0;
    for (int i = 0; i < UART_RX_BUF_LEN; i++) rx_buf[i] = 0;
}

// To be called on RX event (polling or interrupt)
void UART_CommandHandler_ReceiveChar(char c) {
    if (FlapControlLogic_IsBusy()) return;
    if (cmd_valid) return; // Ignore input until cmd is consumed

    if ((c == '\n') || (c == '\r')) {
        if (rx_index > 0) {
            int val = 0; bool valid = true;
            for (int i = 0; i < rx_index; i++) {
                if (rx_buf[i] < '0' || rx_buf[i] > '9') { valid = false; break; }
                val = val * 10 + (rx_buf[i] - '0');
            }
            if (valid && val >= UART_CMD_MIN && val <= UART_CMD_MAX) {
                cmd_valid = true;
                cmd_value = val;
            }
        }
        reset_buf();
    } else if (rx_index < UART_RX_BUF_LEN - 1) {
        rx_buf[rx_index++] = c;
    } else {
        reset_buf(); // overflow or malformed command
    }
}

bool UART_CommandHandler_GetValidCommand(int *cmd_out) {
    if (cmd_valid) {
        *cmd_out = cmd_value;
        cmd_valid = false;
        cmd_value = -1;
        return true;
    }
    return false;
}

bool UART_CommandHandler_IsBusy(void) {
    return cmd_valid; // or add more logic if needed
}

void UART_CommandHandler_Reset(void) {
    reset_buf();
    cmd_valid = false;
    cmd_value = -1;
}
