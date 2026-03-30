#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

// Command queue and status structure
#define CMD_QUEUE_SIZE 4

typedef enum {
    APP_STATE_IDLE,
    APP_STATE_EXECUTE,
    APP_STATE_MONITOR
} AppState_t;

typedef struct {
    int queue[CMD_QUEUE_SIZE];
    int head;
    int tail;
    int status;
} CommandQueue_t;

void ApplicationLayer_Init(CommandQueue_t* q);
void ApplicationLayer_Process(CommandQueue_t* q);

#endif // APPLICATION_LAYER_H
