#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

typedef enum {
    STATE_IDLE = 0,
    STATE_VALIDATE,
    STATE_EXECUTE,
    STATE_OUTPUT,
    STATE_ERROR
} ApplicationState;

void Application_Init(void);
void Application_Process(void);

#endif // APPLICATION_LAYER_H
