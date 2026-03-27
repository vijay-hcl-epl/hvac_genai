#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

typedef enum {
    STATE_IDLE,
    STATE_VALIDATE,
    STATE_EXECUTE,
    STATE_OUTPUT,
    STATE_ERROR
} ApplicationStateType;

typedef struct {
    int requestedCommand;
    ApplicationStateType currentState;
    int isCommandValid;
    int outputRequestState;
} ApplicationLayer_DataType;

void Application_Init(void);
void Application_Process(void);

#endif // APPLICATION_LAYER_H
