#ifndef INPUTHANDLINGUNIT_H
#define INPUTHANDLINGUNIT_H

typedef enum {
    WaitForCommand,
    CommandParse
} InputHandlingState;

typedef struct {
    char uart_buffer[32];
    int uart_buffer_pos;
    int commanded_pos;
    int error_status_flag;
} InputHandlingVars;

void InputHandlingUnit_resp_1();
void InputHandlingUnit_resp_2();

#endif
