#include "command_handler.h"
#include <string.h>
static uint8_t cmd_buf[CMD_BUF_SIZE];
static uint8_t cmd_idx = 0;
static int8_t valid_cmd = -1; // -1 if none
static bool ready = false;
void command_handler_init(void) { cmd_idx = 0; valid_cmd = -1; ready = false; }
void command_handler_rx_char(uint8_t ch)
{
    if (ch >= '0' && ch <= '5') {
        // Accept position chars only
        cmd_buf[0] = ch;
        cmd_idx = 1;
        valid_cmd = (int8_t)(ch - '0');
        ready = true;
    } else {
        // Ignore any invalid input
        cmd_idx = 0;
        valid_cmd = -1;
        ready = false;
    }
}
bool command_handler_command_ready(void) { return ready; }
int8_t get_valid_command(void) {
    if (ready) { ready = false; return valid_cmd; }
    return -1;
}
void command_handler_reset(void) { command_handler_init(); }
