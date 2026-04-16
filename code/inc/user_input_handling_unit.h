#ifndef USER_INPUT_HANDLING_UNIT_H
#define USER_INPUT_HANDLING_UNIT_H

#include <stdint.h>

#define UART_RX_BUFFER_SIZE 16

// Internal Data Design
typedef struct {
    uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];
    int command_value;
} UserInputHandlingUnitData;

// State Machine
typedef enum {
    STATE_WAIT_FOR_INPUT,
    STATE_VALIDATE_INPUT
} UserInputHandlingUnitState;

// Function Declarations
void user_input_handling_unit_resp_0(UserInputHandlingUnitData* data);
void user_input_handling_unit_resp_1(UserInputHandlingUnitData* data);

#endif // USER_INPUT_HANDLING_UNIT_H
