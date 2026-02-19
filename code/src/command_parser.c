#include "command_parser.h"
#include <stddef.h>

const uint8_t allowed_positions[MAX_POSITIONS] = {0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0};

void command_parser_init(command_parser_t *inst)
{
    if (inst == NULL) { return; }
    inst->latest_command = 0U;
    inst->valid = false;
    inst->state = CMD_STATE_INIT;
}

static bool is_allowed_command(uint8_t cmd)
{
    for (unsigned int i = 0; i < MAX_POSITIONS; ++i) {
        if (cmd == allowed_positions[i]) {
            return true;
        }
    }
    return false;
}

void command_parser_process_byte(command_parser_t *inst, uint8_t byte)
{
    if (inst == NULL) { return; }
    inst->state = CMD_STATE_WAIT_RX;
    if (is_allowed_command(byte)) {
        inst->latest_command = byte;
        inst->valid = true;
        inst->state = CMD_STATE_VALID;
    } else {
        inst->valid = false;
        inst->state = CMD_STATE_INVALID;
    }
}

bool command_parser_get_latest(const command_parser_t *inst, uint8_t *pos)
{
    if (inst == NULL || pos == NULL) { return false; }
    if (inst->valid) {
        *pos = inst->latest_command;
        return true;
    }
    return false;
}
