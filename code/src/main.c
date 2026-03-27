#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

int main(void)
{
    // Initialize all units
    ElectricalDriver_Init();
    Hal_Init();
    SignalInterface_Init();
    Application_Init();
    
    while (1) {
        Application_Process();
    }
    return 0;
}
