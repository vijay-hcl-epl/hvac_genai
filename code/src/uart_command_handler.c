#include "uart_command_handler.h"
#include <string.h>
#include <ctype.h>

#define UART_RX_BUF_SIZE 8
static char rx_buffer[UART_RX_BUF_SIZE];
static int rx_pos = 0;
static int parsed_command = 0;
static bool command_ready = false;
static uart_cmd_status_t status = UART_CMD_OK;

void uart_command_handler_init(void) {
    rx_pos = 0;
    command_ready = false;
    status = UART_CMD_OK;
    memset(rx_buffer, 0, sizeof(rx_buffer));
}

void uart_rx_callback(unsigned char byte) {
    if (command_ready) return;
    if (byte == '\n' || byte == '\r') {
        // parse buffer
        if (rx_pos == 0) return;
        rx_buffer[rx_pos] = '\0';
        // all numeric?
        int i;
        for (i = 0; i < rx_pos; i++) {
            if (!isdigit((unsigned char)rx_buffer[i])) {
                status = UART_CMD_ERROR;
                rx_pos = 0;
                memset(rx_buffer, 0, sizeof(rx_buffer));
                return;
            }
        }
        int val = atoi(rx_buffer);
        if (val >= 0 && val <= 100) { // assume 0..100 valid
            parsed_command = val;
            command_ready = true;
            status = UART_CMD_OK;
        } else {
            status = UART_CMD_OOR;
        }
        rx_pos = 0;
        memset(rx_buffer, 0, sizeof(rx_buffer));
    } else if (rx_pos < UART_RX_BUF_SIZE-1) {
        rx_buffer[rx_pos++] = (char)byte;
    } else {
        status = UART_CMD_ERROR;
        rx_pos = 0;
        memset(rx_buffer, 0, sizeof(rx_buffer));
    }
}

bool is_command_ready(void) {
    return command_ready;
}

int get_parsed_command(void) {
    command_ready = false; // clear ready when read
    return parsed_command;
}

uart_cmd_status_t get_uart_cmd_status(void) {
    return status;
}

void uart_command_reset(void) {
    rx_pos = 0;
    command_ready = false;
    status = UART_CMD_OK;
    memset(rx_buffer, 0, sizeof(rx_buffer));
}
