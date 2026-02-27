#include "command_handler.h"
#include "config.h"
#include "state_manager.h"
#include <string.h>

static char cmd_buffer[CMD_BUFFER_SIZE];
static uint8_t cmd_idx = 0;
static cmd_state_t state = CMD_STATE_IDLE;
static uint8_t last_command = 0;
static bool command_available = false;

static void parse_and_validate(void) {
    int val = 0;
    if (sscanf(cmd_buffer, "%d", &val) == 1) {
        if (Config_IsValidPosition((uint8_t)val)) {
            last_command = (uint8_t)val;
            command_available = true;
            state = CMD_STATE_COMPLETE;
            StateManager_OnNewCommand();
        }
        // Ignore invalid positions silently
    }
    // Always reset buffer
    cmd_idx = 0;
    memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
}

void CommandHandler_Init(void) {
    cmd_idx = 0;
    state = CMD_STATE_IDLE;
    command_available = false;
}

void CommandHandler_ReceiveChar(char c) {
    if (state == CMD_STATE_IDLE || state == CMD_STATE_RECEIVING) {
        if (cmd_idx < CMD_BUFFER_SIZE - 1) {
            if (c == '\n' || c == '\r') {
                cmd_buffer[cmd_idx] = 0;
                parse_and_validate();
                state = CMD_STATE_IDLE;
            } else {
                cmd_buffer[cmd_idx++] = c;
                state = CMD_STATE_RECEIVING;
            }
        } else {
            // Buffer overflow, reset
            cmd_idx = 0;
            state = CMD_STATE_ERROR;
            memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
        }
    }
}

bool CommandHandler_IsCommandAvailable(void) {
    return command_available;
}

uint8_t CommandHandler_GetLastCommand(void) {
    command_available = false;
    return last_command;
}

void CommandHandler_Clear(void) {
    cmd_idx = 0;
    command_available = false;
    memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
}
