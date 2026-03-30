#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

typedef enum {
    SIG_IDLE,
    SIG_RECEIVING_DATA,
    SIG_DISPATCHING
} SigIfState_t;

typedef struct {
    int uart_buffer[16];
    int adc_data[8];
    int flap_map[8];
} SignalInterfaceManagerData_t;

void SignalInterfaceManager_Init(void);
void SignalInterfaceManager_Update(void);

#endif // SIGNAL_INTERFACE_MANAGER_H
