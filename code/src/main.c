#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

int main(void) {
    Application_Init();
    while (1) {
        Application_Process();
        // Could use a deterministic sleep/delay here
    }
    return 0;
}
