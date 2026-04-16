#ifndef INPUT_COMMAND_HANDLING_UNIT_H
#define INPUT_COMMAND_HANDLING_UNIT_H

#include <stdint.h>
#include <stdbool.h>

// Internal Data Design
#define UART_BUFFER_SIZE 8
typedef struct {
    char uart_buffer[UART_BUFFER_SIZE];
    uint16_t flap_target;
    bool command_valid;
} InputCommandData_t;

void input_command_resp_1(InputCommandData_t *data, const char *rx_data); // Process UART commands
void input_command_resp_2(InputCommandData_t *data); // Handle invalid input

#endif
