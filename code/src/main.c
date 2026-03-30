#include "ApplicationLayer.h"
#include "SignalInterfaceManager.h"
#include "HardwareAbstractionLayer.h"
#include "ElectricalInterfaceDriver.h"

int main(void) {
    ApplicationLayer_t app_layer;
    SignalInterfaceManager_t sig_if;
    HardwareAbstractionLayer_t hal;
    ElectricalInterfaceDriver_t elec_drv;

    AppLayer_Init(&app_layer);
    SignalIf_Init(&sig_if);
    HAL_Init(&hal);
    ElecDrv_Init(&elec_drv);

    while (1) {
        AppLayer_Run(&app_layer);
        // Pass command to signal manager
        if (app_layer.cmd_valid) {
            SignalIf_ReceiveCommand(&sig_if, app_layer.target_position);
        }
        SignalIf_Run(&sig_if);
        // For demo: if action routed, process in HAL
        if (sig_if.state == FSM_DISPATCH) {
            HAL_ProcessAction(&hal, sig_if.routed_action);
        }
        HAL_Run(&hal);
        // For demo: let HAL trigger electrical op
        if (hal.state == HW_IO_REQUEST) {
            ElecDrv_PerformIO(&elec_drv);
        }
    }
    return 0;
}
