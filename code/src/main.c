#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

static CommandQueue_t app_q;
static SignalBuffer_t sim_buf;
static HalHandle_t hal_table;
static EidHandle_t eid_table;

void system_init(void) {
    ApplicationLayer_Init(&app_q);
    SignalInterfaceManager_Init(&sim_buf);
    HardwareAbstractionLayer_Init(&hal_table);
    ElectricalInterfaceDriver_Init(&eid_table);
}

int main(void) {
    system_init();
    while(1) {
        // Typical embedded superloop
        SignalInterfaceManager_Process(&sim_buf);
        ApplicationLayer_Process(&app_q);
        // Further integration/states omitted for brevity
    }
    return 0;
}
