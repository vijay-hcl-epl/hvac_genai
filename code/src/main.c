#include "application_layer.h"
#include "signal_interface_manager.h"
#include "hw_abstraction_layer.h"
#include "electrical_interface_driver.h"

int main(void) {
    ApplicationLayer_Init();
    SignalInterfaceManager_Init();
    HAL_Init();
    ElectricalInterfaceDriver_Init();
    while(1) {
        ApplicationLayer_Run();
        SignalInterfaceManager_Update();
        ElectricalInterfaceDriver_Update();
    }
    return 0;
}
