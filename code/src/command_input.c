#include "command_input.h"

static int cmd_rx_buffer = CMD_INVALID; // Single-byte UART receive buffer

// Simulated UART receive - must use Infineon TLE9851QXW registers. [TBD — Not found in technical source]
int get_valid_position(void) {
    // Simulate UART receive
    int received = CMD_INVALID;
    // TODO: Read from UART register; if available, update received
    // Example (Pseudocode):
    // if (UART_RX_READY) received = UART_RX_DATA;
    if (received >= CMD_MIN && received <= CMD_MAX) {
        cmd_rx_buffer = received;
        return received;
    } else {
        return CMD_INVALID;
    }
}
