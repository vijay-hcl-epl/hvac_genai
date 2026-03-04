#include "user_cmd_handler.h"
#include "position_ctrl_logic.h"
#include <string.h>

#define RX_BUFFER_SIZE 8

static uint8_t rx_buffer[RX_BUFFER_SIZE];
static uint8_t rx_index = 0;
static cmd_state_t cmd_state = CMD_STATE_IDLE;
static int parsed_target = -1;

void cmd_handler_rx_byte(uint8_t byte) {
    switch (cmd_state) {
        case CMD_STATE_IDLE:
            rx_index = 0;
            rx_buffer[rx_index++] = byte;
            cmd_state = CMD_STATE_RECEIVING;
            break;
        case CMD_STATE_RECEIVING:
            if (rx_index < RX_BUFFER_SIZE) {
                rx_buffer[rx_index++] = byte;
                // Simple example: suppose command is 3 bytes: CMD_PREFIX, POS, CHK
                if (rx_index == 3) {
                    if (rx_buffer[0] == 0xA5 /*CMD_PREFIX example*/ && (rx_buffer[2] == (uint8_t)(rx_buffer[0] ^ rx_buffer[1]))) {
                        parsed_target = rx_buffer[1];
                        cmd_state = CMD_STATE_VALIDATED;
                    } else {
                        cmd_state = CMD_STATE_ERROR;
                    }
                }
            } else {
                cmd_state = CMD_STATE_ERROR;
            }
            break;
        case CMD_STATE_VALIDATED:
        case CMD_STATE_ERROR:
        default:
            // wait for reset
            break;
    }
}

int cmd_handler_get_target(int* pos) {
    if (cmd_state == CMD_STATE_VALIDATED && pos) {
        *pos = parsed_target;
        // Reset for next command
        cmd_state = CMD_STATE_IDLE;
        rx_index = 0;
        parsed_target = -1;
        return 1;
    }
    return 0;
}

void cmd_handler_reset(void) {
    cmd_state = CMD_STATE_IDLE;
    rx_index = 0;
    parsed_target = -1;
    memset(rx_buffer, 0, sizeof(rx_buffer));
}
