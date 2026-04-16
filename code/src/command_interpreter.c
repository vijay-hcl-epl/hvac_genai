#include "command_interpreter.h"
#include <string.h>
#include <stdlib.h>

static char cmd_buffer[CMD_INBUF_SIZE];
static bool command_valid = false;
static uint8_t decoded_command = 0;

void CommandInterpreter_Init(void) {
    memset(cmd_buffer, 0, CMD_INBUF_SIZE);
    command_valid = false;
    decoded_command = 0;
}

// Returns true if buffer parses to integer 0-5, sets valid_cmd_out
bool CommandInterpreter_Validate(const char* rx_buffer, uint8_t* valid_cmd_out) {
    if (!rx_buffer || !valid_cmd_out)
        return false;
    int value = atoi(rx_buffer);
    if (value >= 0 && value <= 5) {
        *valid_cmd_out = (uint8_t)value;
        command_valid = true;
        decoded_command = *valid_cmd_out;
        return true;
    }
    command_valid = false;
    return false;
}
