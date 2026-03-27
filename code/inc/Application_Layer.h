#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

// Data structures for command processing, state, validation

typedef enum {
    APP_STATE_IDLE = 0,
    APP_STATE_COMMAND_RECEIVED,
    APP_STATE_VALIDATING,
    APP_STATE_EXECUTING,
    APP_STATE_OUTPUT_TRIGGERED,
    APP_STATE_ERROR
} AppState_t;

typedef struct {
    int command;
    int validated;
    int output_pending;
} AppCommand_t;

// Application Layer interface
void ApplicationLayer_Init(void);
void ApplicationLayer_Process(void);
void ApplicationLayer_ReceiveCommand(int cmd);
AppState_t ApplicationLayer_GetState(void);

#endif // APPLICATION_LAYER_H
