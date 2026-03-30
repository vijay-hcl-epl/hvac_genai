#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

typedef enum {
    APP_STATE_INIT,
    APP_STATE_WAIT_FOR_COMMAND,
    APP_STATE_MOVING,
    APP_STATE_ERROR
} AppState_t;

typedef struct {
    int target_position;
    int actual_position;
    int init_state;
    int cmd_status;
    AppState_t state;
} ApplicationLayer_t;

void APP_Init(ApplicationLayer_t* app);
void APP_ProcessUART(ApplicationLayer_t* app);
void APP_MoveFlap(ApplicationLayer_t* app);
void APP_CheckError(ApplicationLayer_t* app);

#endif
