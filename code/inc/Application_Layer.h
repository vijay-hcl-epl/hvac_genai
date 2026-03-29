#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>

typedef enum {
    AL_STATE_IDLE,
    AL_STATE_COMMAND_RECEIVED,
    AL_STATE_POSITION_VALIDATION,
    AL_STATE_REQUEST_ISSUED
} ApplicationLayer_State_e;

typedef struct {
    uint8_t currentState;
    uint8_t validCommand;
    uint16_t targetPosition;
} ApplicationLayer_Data_t;

void ApplicationLayer_Init(ApplicationLayer_Data_t *al);
void ApplicationLayer_ProcessCommand(ApplicationLayer_Data_t *al, uint16_t uart_cmd);

#endif // APPLICATION_LAYER_H
