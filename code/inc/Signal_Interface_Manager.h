#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#define SIGNAL_BUF_SIZE 8

typedef enum {
    SIM_STATE_ROUTING,
    SIM_STATE_VALIDATION,
    SIM_STATE_IDLE
} SimState_t;

typedef struct {
    int rx_buf[SIGNAL_BUF_SIZE];
    int tx_buf[SIGNAL_BUF_SIZE];
    int valid_flag;
} SignalBuffer_t;

void SignalInterfaceManager_Init(SignalBuffer_t* s);
void SignalInterfaceManager_Process(SignalBuffer_t* s);

#endif // SIGNAL_INTERFACE_MANAGER_H
