#ifndef INPUT_COMMAND_HANDLING_UNIT_H
#define INPUT_COMMAND_HANDLING_UNIT_H
// Structs from Internal Data Design
typedef struct {
    char uart_buffer[16];
    int flap_target;
    int command_valid;
} InputCommandInternalData;

// Enums from State Machine
typedef enum {
    STATE_RECEIVE_AND_PARSE,
    STATE_CHECK_AND_IGNORE
} InputCommandState;

// Function declarations
void Input_Command_Handling_Unit_resp_0(void);
void Input_Command_Handling_Unit_resp_1(void);

#endif /* INPUT_COMMAND_HANDLING_UNIT_H */
