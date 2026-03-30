#include "Signal_Interface_Manager.h"

void SignalInterfaceManager_Init(SignalBuffer_t* s) {
    s->valid_flag = 0;
    // Zero RX and TX bufs
    for(int i=0; i<SIGNAL_BUF_SIZE; ++i) {
        s->rx_buf[i] = 0;
        s->tx_buf[i] = 0;
    }
}

void SignalInterfaceManager_Process(SignalBuffer_t* s) {
    static SimState_t sim_state = SIM_STATE_IDLE;
    // In a real application: examine buffer, validate, etc.
    switch(sim_state) {
        case SIM_STATE_IDLE:
            sim_state = SIM_STATE_VALIDATION;
            break;
        case SIM_STATE_VALIDATION:
            // Pretend all input valid
            s->valid_flag = 1;
            sim_state = SIM_STATE_ROUTING;
            break;
        case SIM_STATE_ROUTING:
            // Route data, then return to idle
            sim_state = SIM_STATE_IDLE;
            break;
    }
}
