#include "input_management.h"
#include "flap_control_logic.h"
#include <string.h>
#include <stdio.h>

#define UART_CMD_MAX_LEN 16

static char uart_rx_buffer[UART_CMD_MAX_LEN];
static unsigned int uart_rx_len = 0;

void input_mgmt_init(void) {
    memset(uart_rx_buffer, 0, sizeof(uart_rx_buffer));
    uart_rx_len = 0;
}

bool process_uart_rx(const char *buffer, unsigned int len) {
    if (len == 0 || len > UART_CMD_MAX_LEN)
        return false;
    // Accepts ASCII numeric commands for position: e.g. "3\n"
    unsigned int pos = 0;
    if (sscanf(buffer, "%u", &pos) == 1) {
        send_command_to_control(pos);
        return true;
    }
    // Invalid command, ignore
    return false;
}

void send_command_to_control(unsigned int requested_position) {
    start_move(requested_position);
}
