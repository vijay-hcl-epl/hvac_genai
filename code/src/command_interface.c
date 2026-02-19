#include "command_interface.h"
#include "error_handling.h"
#include <string.h>

#define UART_FRAME_LEN   8

static uint8_t rx_buffer[UART_FRAME_LEN];
static uint8_t rx_index = 0;
static command_t current_command = {CMD_TYPE_NONE, 0, false};

enum {
    RX_IDLE,
    RX_RECEIVING,
    RX_VALIDATED,
    RX_ERROR
} rx_state = RX_IDLE;

void command_interface_init(void) {
    rx_index = 0;
    memset(rx_buffer, 0, UART_FRAME_LEN);
    current_command.type = CMD_TYPE_NONE;
    current_command.target_position = 0;
    current_command.valid_command_flag = false;
    rx_state = RX_IDLE;
}

// Simulate UART interrupt handler calling this
void command_interface_receive_byte(uint8_t byte) {
    if (rx_state == RX_IDLE) {
        rx_state = RX_RECEIVING;
        rx_index = 0;
    }
    if (rx_index < UART_FRAME_LEN) {
        rx_buffer[rx_index++] = byte;
        // Simulate frame complete
        if (rx_index == UART_FRAME_LEN) {
            // Minimal parse/validation; here, assume good
            // Example: 1st byte is type, bytes 2-3 is uint16_t position (little endian), byte 7 is CRC
            command_type_t type = (command_type_t) rx_buffer[0];
            uint16_t pos = (uint16_t)rx_buffer[1] | ((uint16_t)rx_buffer[2] << 8);
            // Here, hardware range check is omitted; typically call validation from config
            if ((type == CMD_TYPE_POSITION) && (pos <= 1000)) { // 1000 = example max 
                current_command.type = type;
                current_command.target_position = pos;
                current_command.valid_command_flag = true;
                rx_state = RX_VALIDATED;
            } else {
                current_command.type = CMD_TYPE_NONE;
                current_command.valid_command_flag = false;
                rx_state = RX_ERROR;
                error_handling_set_error(ERR_CMD_INVALID);
            }
        }
    } else {
        rx_state = RX_ERROR;
    }
}

command_t command_interface_get_valid_command(void) {
    return current_command;
}

void command_interface_clear_flag(void) {
    current_command.valid_command_flag = false;
}
