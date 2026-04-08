#ifndef INPUT_COMMAND_HANDLER_H
#define INPUT_COMMAND_HANDLER_H

typedef enum {
    IC_IDLE,
    IC_CMD_RX,
    IC_VALIDATE,
    IC_ACCEPTED,
    IC_REJECTED
} InputCmdState_t;

typedef struct {
    InputCmdState_t state;
    char rx_buffer[32];
    int is_valid;
} InputCmdHandler_t;

void InputCmdHandler_Init(InputCmdHandler_t *ich);
void InputCmdHandler_Receive(InputCmdHandler_t *ich, const char *rx);
void InputCmdHandler_Process(InputCmdHandler_t *ich);

#endif // INPUT_COMMAND_HANDLER_H
