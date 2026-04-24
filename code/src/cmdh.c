#include "cmdh.h"
#include <stdlib.h>
#include <string.h>

static char uart_buf[16];
static int last_cmd_value = CMDH_CMD_INVALID;
static bool last_cmd_valid = false;

void cmdh_init(void) {
    memset(uart_buf, 0, sizeof(uart_buf));
    last_cmd_value = CMDH_CMD_INVALID;
    last_cmd_valid = false;
}

void cmdh_uart_rx_callback(const char *data, uint32_t len) {
    if(!data || len == 0) return;
    // Assume each command is just a single ASCII character [0-5] with optional \n/\r
    for(uint32_t i=0;i<len;++i) {
        if (data[i] >= '0' && data[i] <= '5') {
            last_cmd_value = data[i] - '0';
            last_cmd_valid = true;
        } else if (data[i] == '\n' || data[i] == '\r') {
            // Ignore delimiters
        } else {
            last_cmd_value = CMDH_CMD_INVALID;
            last_cmd_valid = false;
        }
    }
}

bool cmdh_get_last_valid_command(int *cmd_value) {
    if (last_cmd_valid) {
        if (cmd_value) *cmd_value = last_cmd_value;
        last_cmd_valid = false; // One-shot fetch
        return true;
    }
    return false;
}
