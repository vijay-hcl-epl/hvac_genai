#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

typedef enum {
    APP_WAITING_FOR_CMD,
    APP_PROCESS_CMD,
    APP_UPDATE_STATE
} AppState_t;

typedef struct {
    int uart_cmd;
    int current_flap_position;
    int system_state;
} ApplicationLayerData_t;

void ApplicationLayer_Init(void);
void ApplicationLayer_Run(void);

#endif // APPLICATION_LAYER_H
