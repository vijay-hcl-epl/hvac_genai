#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
#include <stdbool.h>
#define CMD_BUF_SIZE 4
// UART RX handler. Accepts/validates commands (0-5), ignores invalid.
void command_handler_init(void);
// Call in main loop or from UART RX event
void command_handler_rx_char(uint8_t ch);
// Returns true if a valid command is available; fetch with get_valid_command().
bool command_handler_command_ready(void);
// Retrieves last valid position command (0-5), or -1 if none.
int8_t get_valid_command(void);
// Resets command handler to idle/empty.
void command_handler_reset(void);
#endif
