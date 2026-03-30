#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

int main(void) {
    ApplicationLayer_t app;
    SignalInterfaceManager_t sim;
    HardwareAbstractionLayer_t hal;
    ElectricalInterfaceDriver_t eid;

    APP_Init(&app);
    SIM_Init(&sim);
    HAL_Init(&hal);

    while (1) {
        APP_ProcessUART(&app);
        SIM_SampleADC(&sim);
        SIM_ValidateADC(&sim);
        HAL_Monitor(&hal);
        EID_MoveMotor(&eid);
        EID_UpdateLED(&eid);
        EID_CheckFault(&eid);
        APP_CheckError(&app);
        // Static - no dynamic alloc, deterministic loop
    }

    return 0;
}
