#include "user_cmd_handler.h"
#include "system_config_data.h"
#include <string.h>

static uint8_t last_cmd_position = 0;
static bool cmd_valid = false;

void user_cmd_handler_init(void) {
    last_cmd_position = 0;
    cmd_valid = false;
}

void user_cmd_handler_receive(uint8_t data) {
    // Assume ASCII 0-5 for position commands
    if (data >= '0' && data <= '5') {
        last_cmd_position = data - '0';
        cmd_valid = true;
    } else {
        cmd_valid = false;
    }
}

bool is_cmd_valid(void) {
    return cmd_valid;
}

uint8_t get_last_cmd_position(void) {
    return last_cmd_position;
}
