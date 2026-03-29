#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

static ApplicationLayer_Data_t application_layer;
static SignalInterface_Data_t signal_manager;
static HardwareAbstraction_Data_t hal;
static ElectricalInterface_Data_t eid;

int main(void) {
    ApplicationLayer_Init(&application_layer);
    SignalInterface_Init(&signal_manager);
    HardwareAbstraction_Init(&hal);
    ElectricalInterface_Init(&eid);

    while (1) {
        uint16_t uart_cmd = 0; // UART stub
        ApplicationLayer_ProcessCommand(&application_layer, uart_cmd);
        SignalInterface_Dispatch(&signal_manager, &application_layer);
        HardwareAbstraction_Actuate(&hal, signal_manager.positionBuffer);
        HardwareAbstraction_UpdateFeedback(&hal);
        ElectricalInterface_Drive(&eid, hal.motorActive);
        ElectricalInterface_Capture(&eid);
    }
    return 0;
}
