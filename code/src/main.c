#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

int main(void) {
    // Initialize all modules
    EID_Init();
    HAL_Init();
    SIM_Init();
    AL_Init();

    while(1) {
        // Deterministic main loop
        EID_MonitorHardware();
        HAL_ReadADC(0);
        SIM_Task();
        AL_Task();
        // Insert small delay or real-time scheduling as needed
    }
    return 0;
}
