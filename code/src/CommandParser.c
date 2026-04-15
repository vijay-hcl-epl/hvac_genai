#include "CommandParser.h"
#include "FlapControlLogic.h"
#include <string.h>

static CommandParser_Cmd_t latest_cmd;
static const uint8_t allowed_cmds[CMD_MAX_POSITIONS] = {0x01, 0x02, 0x03, 0x04, 0x05};

void CommandParser_Init(void) {
    latest_cmd.command = 0;
    latest_cmd.valid = false;
}

void CommandParser_UARTCallback(uint8_t data) {
    latest_cmd.valid = false;
    for (uint8_t i = 0; i < CMD_MAX_POSITIONS; ++i) {
        if (data == allowed_cmds[i]) {
            latest_cmd.command = data;
            latest_cmd.valid = true;
            break;
        }
    }
}

CommandParser_Cmd_t CommandParser_GetLatestCommand(void) {
    return latest_cmd;
}
