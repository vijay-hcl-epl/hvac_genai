#include "uart_cmd_handler.h"
#include "flap_control_logic.h"
#include <string.h>

static uart_cmd_t uart_cmd = { .buffer = {0}, .len = 0, .valid = false, .target_position = 0, .error_type = 0 };
static uart_cmd_state_t state = UART_CMD_IDLE;

void uart_cmd_init(void) {
    memset(&uart_cmd, 0, sizeof(uart_cmd));
    state = UART_CMD_IDLE;
}

void uart_cmd_receive_char(char c) {
    if(state == UART_CMD_IDLE) {
        uart_cmd.len = 0;
        memset(uart_cmd.buffer, 0, UART_CMD_MAX_LEN);
        state = UART_CMD_RECEIVING;
    }
    if(uart_cmd.len < UART_CMD_MAX_LEN-1) {
        uart_cmd.buffer[uart_cmd.len++] = c;
        if(c == '\n') {
            state = UART_CMD_VALIDATING;
        }
    } else {
        state = UART_CMD_ERROR;
        uart_cmd.error_type = 1; // buffer overflow
    }
}

bool uart_cmd_issue_command(int* target_position) {
    if(state == UART_CMD_VALIDATING) {
        // Example: parse number from command string "SET <pos>\n"
        int pos = -1;
        if(sscanf(uart_cmd.buffer, "SET %d", &pos) == 1 && pos >= POS_VALID_MIN && pos <= POS_VALID_MAX) {
            uart_cmd.valid = true;
            uart_cmd.target_position = pos;
            *target_position = pos;
            state = UART_CMD_IDLE;
            return true;
        } else {
            uart_cmd.valid = false;
            uart_cmd.error_type = 2; // invalid format or out of range
            state = UART_CMD_ERROR;
        }
    }
    return false;
}

int uart_cmd_get_last_error(void) {
    return uart_cmd.error_type;
}
