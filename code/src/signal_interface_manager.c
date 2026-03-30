#include "signal_interface_manager.h"
#include "hw_abstraction_layer.h"

static SignalInterfaceManagerData_t sigData;

void SignalInterfaceManager_Init(void) {
    // zero buffers
    for(int i=0;i<16;i++) sigData.uart_buffer[i]=0;
    for(int i=0;i<8;i++) sigData.adc_data[i]=0;
}

void SignalInterfaceManager_Update(void) {
    static SigIfState_t state = SIG_IDLE;
    switch(state) {
        case SIG_IDLE:
            // idle, waiting for data
            state = SIG_RECEIVING_DATA;
            break;
        case SIG_RECEIVING_DATA:
            // Simulate receiving
            state = SIG_DISPATCHING;
            break;
        case SIG_DISPATCHING:
            // conversion
            state = SIG_IDLE;
            break;
        default:
            state = SIG_IDLE;
            break;
    }
}
