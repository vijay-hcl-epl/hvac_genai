#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>
#include <stdbool.h>

// State Machine
typedef enum {
    APP_WAIT_FOR_COMMAND,
    APP_PROCESS_COMMAND
} AppState_t;

// Command buffer and state
typedef struct {
    uint8_t cmd;
    bool cmd_ready;
} ApplicationLayer_Data_t;

void ApplicationLayer_Init(ApplicationLayer_Data_t *data);
void ApplicationLayer_Process(ApplicationLayer_Data_t *data);

#endif // APPLICATION_LAYER_H
