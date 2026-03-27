#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

SignalInterfaceManager_t g_sig_ctx;
ApplicationLayer_t g_app_ctx;

int main(void) {
    ElectricalInterfaceDriver_Init();
    HardwareAbstractionLayer_Init(&g_sig_ctx);
    SignalInterfaceManager_Init(&g_sig_ctx);
    ApplicationLayer_Init(&g_app_ctx);

    while(1) {
        ApplicationLayer_Task(&g_app_ctx);
        SignalInterfaceManager_Task(&g_sig_ctx);
        // HAL/Driver layers called per manager
    }
    return 0;
}
