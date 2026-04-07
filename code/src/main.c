#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

// Static global contexts
static ApplicationLayerContext_t app_ctx;
static SignalInterfaceContext_t sigif_ctx;
static HALContext_t hal_ctx;
static ElectricalDriverContext_t edrv_ctx;

// Simulate a periodic deterministic main loop
int main(void)
{
    // Initialization
    ApplicationLayer_Init(&app_ctx);
    SignalInterfaceManager_Init(&sigif_ctx);
    HardwareAbstractionLayer_Init(&hal_ctx);
    ElectricalInterfaceDriver_Init(&edrv_ctx);

    // Main loop
    while (1) {
        ApplicationLayer_Task(&app_ctx);
        SignalInterfaceManager_Task(&sigif_ctx);
        HardwareAbstractionLayer_Task(&hal_ctx);
        ElectricalInterfaceDriver_Task(&edrv_ctx);
        // Typically, add a RTOS delay/yield here; omitted (no invented functionality)
    }
    return 0;
}
