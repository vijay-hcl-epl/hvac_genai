#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

int main(void)
{
    ApplicationLayerContext app_ctx;
    SignalInterfaceManagerContext sim_ctx;
    HardwareAbstractionLayerContext hal_ctx;
    ElectricalInterfaceDriverContext eid_ctx;

    ApplicationLayer_Init(&app_ctx);
    SignalInterfaceManager_Init(&sim_ctx);
    HardwareAbstractionLayer_Init(&hal_ctx);
    ElectricalInterfaceDriver_Init(&eid_ctx);

    while (1)
    {
        ApplicationLayer_Process(&app_ctx);
        SignalInterfaceManager_Process(&sim_ctx);
        HardwareAbstractionLayer_Process(&hal_ctx);
        ElectricalInterfaceDriver_Process(&eid_ctx);
    }
    return 0;
}
