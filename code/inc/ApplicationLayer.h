#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H
#include <stdint.h>
typedef enum {
    APP_STATE_IDLE,
    APP_STATE_WAITING_FOR_COMMAND,
    APP_STATE_MOVING_TO_POSITION,
    APP_STATE_TARGET_REACHED,
    APP_STATE_ERROR_HANDLING
} AppState;
typedef struct {
    uint8_t current_position;
    uint8_t target_position;
    uint8_t error_flag;
} AppLayerData;
void ApplicationLayer_Init(void);
void ApplicationLayer_Task(void);
void ApplicationLayer_OnCommand(uint8_t pos);
#endif // APPLICATION_LAYER_H
