#include "command_handler.h"
#include <string.h>
#include <ctype.h>

static int last_command_value = 0;
static bool command_valid = false;
static uint8_t rx_buffer[CMD_HANDLER_RX_BUF_SIZE];
static uint16_t rx_idx = 0;

void CommandHandler_Init(void) {
    last_command_value = 0;
    command_valid = false;
    rx_idx = 0;
    memset(rx_buffer, 0, CMD_HANDLER_RX_BUF_SIZE);
}

static bool parse_uart_command(const uint8_t *buf, uint16_t len, int *out_value) {
    if (len == 0 || buf == NULL || out_value == NULL) return false;
    int value = 0;
    uint16_t i = 0;
    while (i < len && isspace(buf[i])) ++i; // skip leading whitespace
    if (i >= len || !isdigit(buf[i])) return false;
    while (i < len && isdigit(buf[i])) {
        value = value * 10 + (buf[i] - '0');
        ++i;
    }
    while (i < len && isspace(buf[i])) ++i;
    if (i != len) return false; // extra non-space chars
    if (value < 0 || value > 5) return false;
    *out_value = value;
    return true;
}

void CommandHandler_UART_RxCallback(const uint8_t *rx_buf, uint16_t len) {
    int parsed = 0;
    if (parse_uart_command(rx_buf, len, &parsed)) {
        last_command_value = parsed;
        command_valid = true;
    } else {
        command_valid = false;
    }
}

bool CommandHandler_GetLastCommand(int *value) {
    if (command_valid && value != NULL) {
        *value = last_command_value;
        return true;
    }
    return false;
}

bool CommandHandler_IsValid(void) {
    return command_valid;
}
