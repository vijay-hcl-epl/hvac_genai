#include "Signal_Interface_Manager.h"
#include "Application_Layer.h"

void SignalInterface_Init(SignalInterface_Data_t *sim) {
    sim->currentState = SIM_STATE_WAIT;
    sim->positionBuffer = 0;
    sim->positionValid = 0;
}

void SignalInterface_Dispatch(SignalInterface_Data_t *sim, const ApplicationLayer_Data_t *al) {
    switch (sim->currentState) {
        case SIM_STATE_WAIT:
            if (al->validCommand) {
                sim->positionBuffer = al->targetPosition;
                sim->positionValid = 1;
                sim->currentState = SIM_STATE_DISPATCH;
            }
            break;
        case SIM_STATE_DISPATCH:
            // Would trigger HAL
            sim->positionValid = 0;
            sim->currentState = SIM_STATE_WAIT;
            break;
        default:
            sim->currentState = SIM_STATE_WAIT;
            break;
    }
}
