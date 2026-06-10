#include "command_manager.h"
#include "flap_control_coordinator.h"
#include <string.h>

// Config: ASCII digit range for positions 0-5
#define CMD_MIN '0'
#define CMD_MAX '5'
#define MAX_CMD_LEN 8

static int command_in_progress = 0;
static uint8_t command_value = 0;
static bool error_flag = false;

void Handle_UART_Command(const char *input) {
    if (command_in_progress) return;
    if (!input || strlen(input) == 0 || strlen(input) > MAX_CMD_LEN)
        goto invalid;
    if (input[1] != '\0')
        goto invalid;
    if (input[0] < CMD_MIN || input[0] > CMD_MAX)
        goto invalid;
    command_value = (uint8_t)(input[0] - '0');
    error_flag = false;
    command_in_progress = 1;
    Process_Position_Request(command_value);
    return;
invalid:
    error_flag = true;
}

// Callback from FlapControl when command processing is complete
void CommandManager_Complete(void) {
    command_in_progress = 0;
}
