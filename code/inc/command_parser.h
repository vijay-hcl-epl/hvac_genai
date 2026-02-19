#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_POSITIONS 8 /* adjustable per config */

typedef enum {
    CMD_STATE_INIT = 0,
    CMD_STATE_WAIT_RX,
    CMD_STATE_VALID,
    CMD_STATE_INVALID
} command_state_t;

typedef struct {
    uint8_t latest_command;
    bool valid;
    command_state_t state;
} command_parser_t;

/* Table of valid positions (size set by config) */
extern const uint8_t allowed_positions[MAX_POSITIONS];

void command_parser_init(command_parser_t *inst);
void command_parser_process_byte(command_parser_t *inst, uint8_t byte);
bool command_parser_get_latest(const command_parser_t *inst, uint8_t *pos);

#endif /* COMMAND_PARSER_H */
