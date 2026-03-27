#include "Signal_Interface_Manager.h"
#include "Electrical_Interface_Driver.h"

void SignalInterface_Init(void) {
    signal_state = STATE_SIGNAL_IDLE;
    signal_raw_input = 0;
    signal_normalized_command = 0;
    signal_normalized_position = 0;
}

int SignalInterface_ReadCommand(void) {
    signal_state = STATE_SIGNAL_READ;
    int raw = ElectricalDriver_ReadInput();
    // Normalize value
    if (raw >= 0 && raw < 100) {
        signal_normalized_command = raw / 10;
        signal_state = STATE_SIGNAL_NORMALIZE;
        return signal_normalized_command;
    } else {
        signal_state = STATE_SIGNAL_ERROR;
        return -1; // Invalid
    }
}

int SignalInterface_ReadPosition(void) {
    int sample = ElectricalDriver_ReadAdc();
    return sample; // No normalization for demo
}
