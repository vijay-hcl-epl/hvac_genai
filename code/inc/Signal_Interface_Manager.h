#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H
#include <stdint.h>

typedef enum {
    SIM_STATE_IDLE = 0,
    SIM_STATE_ROUTE_UART,
    SIM_STATE_ROUTE_LED,
    SIM_STATE_WAIT_UPPER,
    SIM_STATE_WAIT_LOWER
} SignalInterfaceManagerState;

typedef struct {
    uint8_t uart_buffer[8];
    uint8_t led_state;
    SignalInterfaceManagerState state;
} SignalInterfaceManagerContext;

void SignalInterfaceManager_Init(SignalInterfaceManagerContext *ctx);
void SignalInterfaceManager_Process(SignalInterfaceManagerContext *ctx);

#endif // SIGNAL_INTERFACE_MANAGER_H
