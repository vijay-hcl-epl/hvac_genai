#include "Application_Layer.h"

void ApplicationLayer_Init(ApplicationLayer_Data_t *al) {
    al->currentState = AL_STATE_IDLE;
    al->validCommand = 0;
    al->targetPosition = 0;
}

void ApplicationLayer_ProcessCommand(ApplicationLayer_Data_t *al, uint16_t uart_cmd) {
    switch (al->currentState) {
        case AL_STATE_IDLE:
            // Receive UART command
            al->targetPosition = uart_cmd;
            al->currentState = AL_STATE_COMMAND_RECEIVED;
            break;
        case AL_STATE_COMMAND_RECEIVED:
            // Validate position
            if (uart_cmd >= 0 && uart_cmd <= 1000) {
                al->validCommand = 1;
            } else {
                al->validCommand = 0;
            }
            al->currentState = AL_STATE_POSITION_VALIDATION;
            break;
        case AL_STATE_POSITION_VALIDATION:
            if (al->validCommand) {
                al->currentState = AL_STATE_REQUEST_ISSUED;
            } else {
                // Ignore invalid
                al->currentState = AL_STATE_IDLE;
            }
            break;
        case AL_STATE_REQUEST_ISSUED:
            // Would trigger next module
            al->currentState = AL_STATE_IDLE;
            break;
        default:
            al->currentState = AL_STATE_IDLE;
            break;
    }
}
