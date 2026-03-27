#include "signal_interface_manager.h"
#include "hardware_abstraction_layer.h"

static SignalState_t sigState = SIGNAL_IDLE;
static SignalData_t sigData;

void SignalInterfaceManager_Init(void) {
    sigState = SIGNAL_IDLE;
    sigData.adc_value = 0;
    sigData.relay_state = 0;
    sigData.led_status = 0;
}

void SignalInterfaceManager_HandleCommand(uint8_t command) {
    // Validate and translate command
    // Relays signal to hardware abstraction layer
    sigState = SIGNAL_UPDATE;
}

void SignalInterfaceManager_UpdateSignals(void) {
    if (sigState == SIGNAL_UPDATE) {
        // Example: update ADC, LED, relay via HAL
        sigData.adc_value = HAL_ReadADC();
        sigData.led_status = HAL_GetLEDStatus();
        HAL_SetRelay(sigData.relay_state);
        sigState = SIGNAL_DISPATCH;
    }
    if (sigState == SIGNAL_DISPATCH) {
        // TODO: additional propagation logic
        sigState = SIGNAL_IDLE;
    }
}
