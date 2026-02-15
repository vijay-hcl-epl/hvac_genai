#include "uart_cmd_if.h"
#include "hal_uart.h"
#define CMD_BUF_SIZE 8
#define INVALID_CMD 0xFF
static char input_buf[CMD_BUF_SIZE];
static uint8_t buf_idx = 0;
static uint8_t cmd_ready = 0;
static uint8_t parsed_cmd = INVALID_CMD;

enum { IDLE, RECEIVING } rx_state = IDLE;

void uart_cmd_if_init(void) { buf_idx = 0; cmd_ready = 0; parsed_cmd = INVALID_CMD; rx_state = IDLE; }

bool uart_cmd_if_parsed_cmd_available(void) { return (cmd_ready != 0); }

uint8_t uart_cmd_if_get_command(void) { cmd_ready = 0; return parsed_cmd; }

void uart_cmd_if_rx_handler(void) {
    while (hal_uart_char_available() != 0) {
        char c = hal_uart_read_char();
        if (rx_state == IDLE) {
            buf_idx = 0;
            rx_state = RECEIVING;
        }
        if ((c == '\n') || (c == '\r')) {
            input_buf[buf_idx] = '\0';
            int val = -1;
            /* MISRA: Violation not auto-fixed – manual review required: sscanf usage (Rule 21.6) */
            if ((sscanf(input_buf, "%d", &val) == 1) && (val >= 0) && (val <= 5)) {
                parsed_cmd = (uint8_t)val;
                cmd_ready = 1U;
            } else {
                parsed_cmd = INVALID_CMD;
            }
            rx_state = IDLE;
            buf_idx = 0U;
        } else if ((buf_idx < (CMD_BUF_SIZE - 1U)) && (c >= '0') && (c <= '9')) {
            input_buf[buf_idx] = c;
            buf_idx++;
        } else {
            rx_state = IDLE;
            buf_idx = 0U;
        }
    }
}
