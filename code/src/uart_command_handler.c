#include "uart_command_handler.h"
#include "main_control_logic.h"
#include <string.h>

static uint8_t rx_buf[UART_CMD_MAX_LEN];
static uint8_t rx_len = 0;

void uart_command_handler_init(void) {
  rx_len = 0;
}

void uart_command_handler_rx_byte(uint8_t byte) {
  if (byte == '\n' || rx_len >= UART_CMD_MAX_LEN) {
    rx_buf[rx_len] = 0;
    int pos = -1;
    if (sscanf((char*)rx_buf, "%d", &pos) == 1 && pos >= 0 && pos <= 4) {
      main_control_logic_on_position_cmd((uint8_t)pos);
    }
    rx_len = 0;
    return;
  }
  if (rx_len < UART_CMD_MAX_LEN) {
    rx_buf[rx_len++] = byte;
  }
}
