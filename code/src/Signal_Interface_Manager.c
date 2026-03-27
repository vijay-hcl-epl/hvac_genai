#include "Signal_Interface_Manager.h"
#include "Electrical_Interface_Driver.h"

static SignalInterface_Data_t signalData;

int SignalInterface_ReadCommand(void) {
    signalData.rawInputValue = ElectricalDriver_ReadInput();
    if (signalData.rawInputValue < 0) {
        return -1;
    }
    // Normalize: 0=open, 1=close, 2=stop
    if (signalData.rawInputValue == 0) {
        signalData.normalizedCommand = 1; // open
        return 1;
    } else if (signalData.rawInputValue == 1) {
        signalData.normalizedCommand = 2; // close
        return 2;
    } else if (signalData.rawInputValue == 2) {
        signalData.normalizedCommand = 3; // stop
        return 3;
    } else {
        return -1; // invalid
    }
}

int SignalInterface_ReadPosition(void) {
    int sample = ElectricalDriver_ReadAdc();
    if (sample < 0) {
        return -1;
    }
    signalData.normalizedPosition = sample; // No further processing
    return signalData.normalizedPosition;
}
