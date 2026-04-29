#include "command_handler.h"
#include <stdint.h>
#include <stdbool.h>
// UART receive stub; replace with HAL_UART_Receive()
static const uint8_t valid_positions[6] = {0,1,2,3,4,5};

// Dummy read from UART; replace with actual HAL_UART_Receive IT/non-blocking
static int uart_receive(uint8_t* c) {
    // Should be replaced by real non-blocking UART driver
    // simulate no data
    return 0; // 0 on no data, 1 on data
}

CmdParseStatus command_handler_poll(uint8_t* cmd_out) {
    uint8_t rx = 0U;
    if (uart_receive(&rx) == 0) {
        return CMD_PARSE_EMPTY;
    }
    // Convert from ASCII ('0'-'5')
    if (rx < '0' || rx > '5') {
        return CMD_PARSE_INVALID;
    }
    uint8_t val = rx - '0';
    for (uint8_t i = 0; i < 6U; ++i) {
        if (val == valid_positions[i]) {
            *cmd_out = val;
            return CMD_PARSE_OK;
        }
    }
    return CMD_PARSE_INVALID;
}
