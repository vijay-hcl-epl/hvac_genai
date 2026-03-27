#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

// State machine for application
typedef enum {
    APP_STATE_IDLE,
    APP_STATE_VALIDATE,
    APP_STATE_EXECUTE,
    APP_STATE_OUTPUT,
    APP_STATE_ERROR
} ApplicationState_t;

// Commands for application
typedef enum {
    APP_CMD_NONE,
    APP_CMD_OPEN,
    APP_CMD_CLOSE,
    APP_CMD_STOP,
    APP_CMD_INVALID
} ApplicationCommand_t;

typedef struct {
    ApplicationCommand_t requestedCommand;
    ApplicationState_t currentState;
    int isValid;
    int outputRequest;
} ApplicationLayer_Data_t;

void Application_Init(void);
void Application_Process(void);

#endif // APPLICATION_LAYER_H
