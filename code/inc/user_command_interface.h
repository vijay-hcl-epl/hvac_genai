#ifndef USER_COMMAND_INTERFACE_H
#define USER_COMMAND_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

#define UART_CMD_BUFFER_SIZE 8
#define NUM_FLAP_POSITIONS 5

// List of valid position commands (change as per requirements)
extern const uint8_t valid_position_indices[NUM_FLAP_POSITIONS];

// Structure for parsed command
typedef struct {
    uint8_t position_index;
    bool valid;
} user_command_t;

// Initialize the user command interface (buffer, state, etc.)
void user_command_interface_init(void);

// Should be called for each received UART byte
void user_command_interface_receive_byte(uint8_t rx_byte);

// Get the latest valid command: returns a copy
user_command_t get_user_command(void);

#endif // USER_COMMAND_INTERFACE_H
