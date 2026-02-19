#ifndef CMD_INPUT_H
#define CMD_INPUT_H
#include <stdint.h>

// Possible user command range
#define CMD_POS_MIN 0
#define CMD_POS_MAX 5
#define CMD_INVALID 255

// Returns most recent valid decoded position [0:5] or CMD_INVALID
uint8_t get_decoded_command(void);

// Should be called by UART RX ISR/callback with received character
void cmd_input_on_uart_rx(uint8_t rx_byte);

#endif // CMD_INPUT_H
