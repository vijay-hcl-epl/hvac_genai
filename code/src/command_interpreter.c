#include "command_interpreter.h"
#include "flap_control.h"
#include "hw_interface.h"

#define CMD_BUF_SIZE 4
static uint8_t command_buffer[CMD_BUF_SIZE];
static uint8_t last_command = 0xFF;
static bool    cmd_valid = false;

void command_interpreter_init(void) {
    // Placeholder: UART driver setup if needed
}

int accept_command(uint8_t cmd)
{
    if (cmd == last_command)
        return CMD_REPEATED;
    if (cmd > 7)
        return CMD_INVALID;
    last_command = cmd;
    cmd_valid = true;
    set_target_position(cmd);
    return CMD_OK;
}
