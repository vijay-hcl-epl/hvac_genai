#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>

typedef enum {
    APP_STATE_IDLE = 0,
    APP_STATE_RECEIVE_COMMAND,
    APP_STATE_PARSE_COMMAND,
    APP_STATE_DISPATCH_REQUEST,
    APP_STATE_WAIT_CONFIRM
} ApplicationLayerState;

typedef struct {
    uint8_t command_buffer[8];
    uint8_t target_position;
    ApplicationLayerState state;
} ApplicationLayerContext;

void ApplicationLayer_Init(ApplicationLayerContext *ctx);
void ApplicationLayer_Process(ApplicationLayerContext *ctx);

#endif // APPLICATION_LAYER_H
