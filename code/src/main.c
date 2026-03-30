#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

static ApplicationLayer_Data_t app_data;
static SignalInterfaceManager_Data_t sim_data;
static HardwareAbstractionLayer_Data_t hal_data;

int main(void)
{
    ElectricalInterfaceDriver_Init();
    HardwareAbstractionLayer_Init(&hal_data);
    SignalInterfaceManager_Init(&sim_data);
    ApplicationLayer_Init(&app_data);

    while (1)
    {
        // Simulate UART RX
        // If UART interrupt: SignalInterfaceManager_UARTInterrupt(&sim_data, RxByte);

        // App logic
        ApplicationLayer_Process(&app_data);
        HardwareAbstractionLayer_Periodic(&hal_data);
        // (Other tasks)
    }
    return 0;
}
