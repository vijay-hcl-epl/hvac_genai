#include "command_parser.h"
#include <string.h>

// Allowed positions (example: flap 0-3)
static const uint8_t allowed_positions[] = {0x00, 0x01, 0x02, 0x03};
static uint8_t latest_command = CMD_POSITION_INVALID;
static bool command_valid = false;

void command_parser_init(void) {
    latest_command = CMD_POSITION_INVALID;
    command_valid = false;
}

void command_parser_receive_byte(uint8_t byte) {
    command_valid = false;
    for (size_t i = 0; i < sizeof(allowed_positions); ++i) {
        if (byte == allowed_positions[i]) {
            latest_command = byte;
            command_valid = true;
            return;
        }
    }
    latest_command = CMD_POSITION_INVALID;
    // command_valid remains false
}

bool command_parser_get_latest_command(uint8_t *position, bool *valid) {
    if (position && valid) {
        *position = latest_command;
        *valid = command_valid;
        return true;
    }
    return false;
}
