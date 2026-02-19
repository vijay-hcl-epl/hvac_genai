#include "cmd_input.h"
#include <stdbool.h>

static uint8_t last_cmd = CMD_INVALID;

void cmd_input_on_uart_rx(uint8_t rx_byte) {
    if (rx_byte >= '0' && rx_byte <= '5') {
        last_cmd = rx_byte - '0';
    } else {
        last_cmd = CMD_INVALID;
    }
}

uint8_t get_decoded_command(void) {
    return last_cmd;
}
