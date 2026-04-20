#include "command_handler.h"
#include "config_calib.h"
#define INVALID_CMD 255
static uint8_t pending_command = INVALID_CMD;
static bool command_ready = false;
static uint8_t parse_fail_count = 0;
void uart_rx_handler(uint8_t byte_in) {
    if (byte_in >= '0' && byte_in <= '5' && !command_ready) {
        pending_command = byte_in - '0';
        command_ready = true;
    } else {
        parse_fail_count++;
    }
}
int get_next_command(void) {
    if (command_ready) {
        command_ready = false;
        uint8_t cmd = pending_command;
        pending_command = INVALID_CMD;
        return cmd;
    }
    return INVALID_CMD;
}
bool is_command_ready(void) {
    return command_ready;
}
