#ifndef INPUT_HANDLING_UNIT_H
#define INPUT_HANDLING_UNIT_H

#include <stdint.h>
#define UART_BUFFER_SIZE 16

typedef struct {
    uint8_t uart_buffer[UART_BUFFER_SIZE];
    uint8_t parsed_command;
    uint8_t is_valid;
    uint8_t ignore_flag;
    uint8_t consecutive_invalid;
} InputHandlingUnitData;

typedef enum {
    IHU_WAIT_FOR_UART_DATA = 0,
    IHU_PARSE_INPUT,
    IHU_VALIDATE_COMMAND,
    IHU_INVALID_COMMAND,
    IHU_IGNORE_AND_WAIT
} InputHandlingUnitState;

void Input_Handling_Unit_resp_1(InputHandlingUnitData* data);
void Input_Handling_Unit_resp_2(InputHandlingUnitData* data);
void Input_Handling_Unit_resp_3(InputHandlingUnitData* data);

#endif // INPUT_HANDLING_UNIT_H
