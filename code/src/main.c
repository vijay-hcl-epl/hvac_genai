#include "hardware_abstraction.h"
#include "command_manager.h"
#include "led_management.h"
#include "flap_control_coordinator.h"
#include <stdio.h>

int main(void) {
    Init_Hardware();
    Set_Status_LED(true);
    uint8_t pos = Get_Current_Position();
    Set_Position_LED(pos != 0xFF ? pos : 0);
    // Main loop stub for polling UART and periodic feedback sample
    while (1) {
        // Simulation: handle some example UART command
        // e.g., Handle_UART_Command("2");
        // Periodically update feedback to flap control
        FlapControl_Feedback_Update(Get_Current_Position());
        // Sleep, wait for events, etc. (not implemented)
        break; // Remove or replace with real event loop
    }
    return 0;
}
