#include "application_layer.h"
#include "signal_interface_manager.h"
#include "hardware_abstraction_layer.h"

int main(void) {
    HAL_Init();
    SignalInterfaceManager_Init();
    ApplicationLayer_Init();
    while (1) {
        ApplicationLayer_ExecCycle();
        SignalInterfaceManager_UpdateSignals();
        // Deterministic loop
    }
    return 0;
}
