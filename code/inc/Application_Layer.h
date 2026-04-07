#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>
typedef enum {
    APP_STATE_IDLE,
    APP_STATE_CMD_PROCESSING,
    APP_STATE_INVOKE_POSITION
} ApplicationLayerState_t;

typedef struct {
    char uart_cmd_buffer[32];
    uint8_t uart_cmd_parser_state;
    uint16_t target_flap_position;
    ApplicationLayerState_t state;
} ApplicationLayerContext_t;

void ApplicationLayer_Init(ApplicationLayerContext_t* ctx);
void ApplicationLayer_Task(ApplicationLayerContext_t* ctx);
int ApplicationLayer_ParseUARTInput(ApplicationLayerContext_t* ctx, const char* uart_in);

#endif // APPLICATION_LAYER_H
