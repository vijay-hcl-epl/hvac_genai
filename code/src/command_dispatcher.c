#include "command_dispatcher.h"
#include "flap_control.h"

static int last_cmd_position = -1;
static int last_cmd_valid = 0;
// Acceptable positions: 0-5
#define MIN_POS 0
#define MAX_POS 5

static int valid_position(int pos) {
    return (pos >= MIN_POS) && (pos <= MAX_POS);
}

int CommandDispatcher_ReceiveCommand(const uint8_t* data, size_t len) {
    if (len < 1) return -1;
    int position = (int)data[0];
    if (valid_position(position)) {
        last_cmd_position = position;
        last_cmd_valid = 1;
        FlapControl_SetTargetPosition(position);
        return 1;
    } else {
        last_cmd_valid = 0;
        return -1; // Invalid/malformed
    }
}

int CommandDispatcher_GetNextTarget(int* pos_out) {
    if (last_cmd_valid && pos_out) {
        *pos_out = last_cmd_position;
        last_cmd_valid = 0;
        return 1;
    }
    return 0;
}

void CommandDispatcher_NotifyIdle(void) {
    last_cmd_valid = 0;
}
