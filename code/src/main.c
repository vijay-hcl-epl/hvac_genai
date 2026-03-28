#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

int main(void) {
    // System initialization
    HAL_Init();
    EID_Init();
    APP_Init();
    SIM_Init();
    
    while(1) {
        HAL_Task();
        EID_Task();
        SIM_Task();
        APP_Task();
        // Deterministic control loop
    }
    return 0;
}
