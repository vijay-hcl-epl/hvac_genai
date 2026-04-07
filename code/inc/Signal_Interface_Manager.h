#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#include <stdint.h>
typedef enum {
    SIGIF_STATE_IDLE,
    SIGIF_STATE_CONVERTING,
    SIGIF_STATE_FORWARD
} SignalInterfaceState_t;

typedef struct {
    uint16_t target_position_input;
    uint16_t digital_position;
    uint8_t status_flags;
    SignalInterfaceState_t state;
} SignalInterfaceContext_t;

void SignalInterfaceManager_Init(SignalInterfaceContext_t* ctx);
void SignalInterfaceManager_Task(SignalInterfaceContext_t* ctx);
void SignalInterfaceManager_SetTargetPosition(uint16_t target_pos);

#endif // SIGNAL_INTERFACE_MANAGER_H
