#include "user_command_handler.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static uint8_t error_count = 0;
static uint16_t last_valid_command = 0;

void user_command_handler_init(void) {
    error_count = 0;
    last_valid_command = 0;
}

CmdStatus_t parse_user_command(const char *uart_data, uint16_t *parsed_position) {
    if (uart_data == NULL || parsed_position == NULL) {
        error_count++;
        return CMD_INVALID;
    }
    size_t len = strlen(uart_data);
    if (len < 3 || len > (CMD_LEN_MAX - 1)) {
        error_count++;
        return CMD_INVALID;
    }
    // Expecting: "SET:<pos>\n" where <pos> is 0-3
    if (strncmp(uart_data, "SET:", 4) != 0) {
        error_count++;
        return CMD_INVALID;
    }
    char pos_char = uart_data[4];
    if (!isdigit((unsigned char)pos_char)) {
        error_count++;
        return CMD_INVALID;
    }
    uint16_t pos = (uint16_t)(pos_char - '0');
    if (pos > 3) {
        error_count++;
        return CMD_INVALID;
    }
    *parsed_position = pos;
    last_valid_command = pos;
    return CMD_VALID;
}

uint8_t user_command_handler_get_error_count(void) {
    return error_count;
}
