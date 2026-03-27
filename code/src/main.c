#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

void main(void) {
    // Initialize all software units
    ElectricalDriver_ReadAdc();      // Initialize ADC hardware simulation
    Application_Init();
    
    while (1) {
        Application_Process();
    }
}
