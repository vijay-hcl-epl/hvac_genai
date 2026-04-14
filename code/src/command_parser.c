#include "command_parser.h"
#include "main.h" // For UART handle

const uint8_t cmd_position_table[CMD_POSITION_TABLE_SIZE] = {0x10, 0x20, 0x30, 0x40}; // Example allowed

static command_t cmd_ctx = {0, false};
static cmd_parser_state_t state = CMD_STATE_INIT;

void command_parser_init(void) {
    state = CMD_STATE_WAIT_RX;
    cmd_ctx.latest_cmd = 0;
    cmd_ctx.valid = false;
}

void command_parser_on_uart_rx(uint8_t rx_byte) {
    bool match = false;
    for (uint8_t i = 0; i < CMD_POSITION_TABLE_SIZE; ++i) {
        if (rx_byte == cmd_position_table[i]) {
            match = true;
            break;
        }
    }
    if (match) {
        cmd_ctx.latest_cmd = rx_byte;
        cmd_ctx.valid = true;
        state = CMD_STATE_VALID;
    } else {
        cmd_ctx.valid = false;
        state = CMD_STATE_INVALID;
    }
}

command_t command_parser_get_latest(void) {
    return cmd_ctx;
}
