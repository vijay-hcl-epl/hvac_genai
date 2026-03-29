#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#include <stdint.h>

typedef enum {
    SIM_STATE_WAIT,
    SIM_STATE_VALIDATING,
    SIM_STATE_DISPATCH
} SignalInterface_State_e;

typedef struct {
    uint8_t currentState;
    uint16_t positionBuffer;
    uint8_t positionValid;
} SignalInterface_Data_t;

void SignalInterface_Init(SignalInterface_Data_t *sim);
void SignalInterface_Dispatch(SignalInterface_Data_t *sim, const ApplicationLayer_Data_t *al);

#endif // SIGNAL_INTERFACE_MANAGER_H
