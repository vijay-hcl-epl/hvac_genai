#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#include <stdint.h>

// Signal states
typedef enum {
    SIGNAL_IDLE,
    SIGNAL_UPDATE,
    SIGNAL_DISPATCH
} SignalState_t;

typedef struct {
    uint16_t adc_value;
    uint8_t relay_state;
    uint8_t led_status;
} SignalData_t;

void SignalInterfaceManager_Init(void);
void SignalInterfaceManager_HandleCommand(uint8_t command);
void SignalInterfaceManager_UpdateSignals(void);

#endif // SIGNAL_INTERFACE_MANAGER_H
