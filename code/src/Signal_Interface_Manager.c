#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

void SignalInterfaceManager_Init(SignalInterfaceManager_Data_t *data) {
    data->buf[0] = 0;
    data->valid = false;
    data->state = SIM_IDLE;
}

void SignalInterfaceManager_UARTInterrupt(SignalInterfaceManager_Data_t *data, uint8_t rx) {
    data->buf[0] = rx;
    data->state = SIM_PARSE_UART;
}

bool SignalInterfaceManager_ValidateCommand(uint8_t cmd) {
    // Only 0-5 valid
    if (cmd <= 5) {
        return true;
    }
    return false;
}

void SignalInterfaceManager_RelayCommand(uint8_t cmd) {
    HardwareAbstractionLayer_ReceiveCommand(cmd);
}
