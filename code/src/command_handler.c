#include "command_handler.h"
#include "state_manager.h"

static volatile uint8_t latest_cmd = CMD_INVALID;
static volatile bool cmd_ready = false;

void command_handler_init(void)
{
    latest_cmd = CMD_INVALID;
    cmd_ready = false;
}

void command_handler_receive(uint8_t data)
{
    if(state_manager_get_state() != STATE_IDLE)
    {
        return;
    }
    if(data >= 0 && data <= 5)
    {
        latest_cmd = data;
        cmd_ready = true;
    }
    // else: invalid, silently ignore
}

bool command_handler_get_new_command(uint8_t* position)
{
    if(cmd_ready && position != 0)
    {
        *position = latest_cmd;
        cmd_ready = false;
        return true;
    }
    return false;
}
