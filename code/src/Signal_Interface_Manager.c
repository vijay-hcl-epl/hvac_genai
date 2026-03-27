#include "Signal_Interface_Manager.h"
#include "Electrical_Interface_Driver.h"

static SignalInterfaceManager_DataType signalData;

int SignalInterface_ReadCommand(void) {
    signalData.rawInputValue = ElectricalDriver_ReadInput();
    if (signalData.rawInputValue >= 0 && signalData.rawInputValue <= 100) {
        signalData.normalizedCommand = signalData.rawInputValue;
        return signalData.normalizedCommand;
    } else {
        return -1; // Invalid command
    }
}

int SignalInterface_ReadPosition(void) {
    signalData.normalizedPosition = ElectricalDriver_ReadAdc();
    return signalData.normalizedPosition;
}
