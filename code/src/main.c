#include "command_interface.h"
#include "position_control.h"
#include "sensing.h"
#include "feedback.h"
#include "hardware_abstraction.h"
#include <string.h>

int main(void) {
    HA_Init();
    SENS_Init();
    FB_Init();
    CI_Init();
    PC_Init();
    while (1) {
        // Periodically sample position
        SENS_PeriodicSample();
        // Main control actuation loop
        PC_LoopTask();
        // Feedback LEDs can be updated here or by callback (not implemented in this stub)
    }
    return 0;
}
