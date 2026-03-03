#include "command_handler.h"
#include <string.h>
#include <stdlib.h>

static int cmd_target_position = CMD_FLAP_POS_MIN;
static CMD_Status_t cmd_status = CMD_INVALID;
static bool cmd_pending = false;

void CMD_Init(void) {
    cmd_target_position = CMD_FLAP_POS_MIN;
    cmd_status = CMD_INVALID;
    cmd_pending = false;
}

CMD_Status_t CMD_ParseAndValidate(const uint8_t *input, uint8_t len) {
    char tempbuf[8] = {0};
    int num = 0;
    if (len > 0 && len < sizeof(tempbuf)) {
        memcpy(tempbuf, input, len);
        tempbuf[len] = 0; // Null terminate
        char *endptr = NULL;
        num = (int)strtol(tempbuf, &endptr, 10);
        if (endptr != NULL && *endptr == '\0') {
            // Valid integer, now check range
            if (num >= CMD_FLAP_POS_MIN && num <= CMD_FLAP_POS_MAX) {
                cmd_target_position = num;
                cmd_status = CMD_VALID;
                cmd_pending = true;
                return CMD_VALID;
            } else {
                cmd_status = CMD_OUT_OF_RANGE;
            }
        } else {
            cmd_status = CMD_INVALID;
        }
    } else {
        cmd_status = CMD_INVALID;
    }
    cmd_pending = false;
    return cmd_status;
}

int CMD_GetTargetPosition(void) {
    if (cmd_status == CMD_VALID && cmd_pending) {
        return cmd_target_position;
    }
    return -1;
}

void CMD_Consume(void) {
    cmd_status = CMD_INVALID;
    cmd_pending = false;
}

bool CMD_HasValidCommand(void) {
    return (cmd_status == CMD_VALID && cmd_pending);
}

void CMD_ClearError(void) {
    if (cmd_status != CMD_VALID) {
        cmd_status = CMD_INVALID;
    }
}
