#include "uart_command_handler.h"
#include <string.h>
#include <ctype.h>

static uint8_t rx_buf[UART_CMD_MAX_LEN+1];
static uint8_t rx_idx = 0;
static uart_cmd_cb_t cmd_cb = 0;

void uart_command_handler_init(uart_cmd_cb_t cb)
{
    rx_idx = 0;
    cmd_cb = cb;
}

void uart_command_handler_receive(uint8_t byte)
{
    if (byte == '\n' || byte == '\r' || rx_idx >= UART_CMD_MAX_LEN) {
        rx_buf[rx_idx] = 0;
        // Parse
        uint8_t num = 0; bool valid = true;
        for(uint8_t i=0; i<rx_idx; i++) {
            if (!isdigit(rx_buf[i])) { valid = false; break; }
            num = num * 10 + (rx_buf[i] - '0');
        }
        if (valid && cmd_cb) cmd_cb(num, true);
        // Discard on invalid
        rx_idx = 0;
    } else {
        rx_buf[rx_idx++] = byte;
    }
}
