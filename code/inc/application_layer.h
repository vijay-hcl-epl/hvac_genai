#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>

// State machine for Application Layer
typedef enum {
    APP_IDLE,
    APP_PARSE_CMD,
    APP_EXECUTE_ACTION,
    APP_ACK
} ApplicationState_t;

// Command context
typedef struct {
    uint8_t command;
    uint8_t valid;
} AppCommandContext_t;

void ApplicationLayer_Init(void);
void ApplicationLayer_ExecCycle(void);

#endif // APPLICATION_LAYER_H
