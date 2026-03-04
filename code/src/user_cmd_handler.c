#include "user_cmd_handler.h"
#include "system_config_data.h"
#define CMD_VALID_MIN   0
#define CMD_VALID_MAX   (SYSTEM_POSITION_COUNT-1)
static uint8_t last_valid_cmd = 0;
static bool command_in_progress = false;

void UserCmdHandler_Process(uint8_t rx_byte) {
    if (rx_byte >= CMD_VALID_MIN && rx_byte <= CMD_VALID_MAX) {
        last_valid_cmd = rx_byte;
        command_in_progress = true;
    }
}

uint8_t UserCmdHandler_GetTarget(void) {
    command_in_progress = false;
    return last_valid_cmd;
}

bool UserCmdHandler_CommandInProgress(void) {
    return command_in_progress;
}
