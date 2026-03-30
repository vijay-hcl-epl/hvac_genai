#include "signal_interface_manager.h"
#include "hardware_abstraction_layer.h"

static int target_position = 0;

void SIM_SetTargetPosition(int position) {
    if (position >= 0 && position <= 5) {
        target_position = position;
        EID_PerformOperation(target_position);
    } // Out of range commands handled upstream
}
