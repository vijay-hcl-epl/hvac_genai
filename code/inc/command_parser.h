#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <stdbool.h>

// Allowed positions table (customizable)
#define CMD_POSITION_TABLE_SIZE 4
extern const uint8_t cmd_position_table[CMD_POSITION_TABLE_SIZE];

// States for Command Parser
typedef enum {
    CMD_STATE_INIT,
    CMD_STATE_WAIT_RX,
    CMD_STATE_VALID,
    CMD_STATE_INVALID
} cmd_parser_state_t;

// Command structure
typedef struct {
    uint8_t latest_cmd;
    bool valid;
} command_t;

// API
void command_parser_init(void);
void command_parser_on_uart_rx(uint8_t rx_byte);
command_t command_parser_get_latest(void);

#endif // COMMAND_PARSER_H
