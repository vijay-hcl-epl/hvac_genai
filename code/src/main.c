#include "command_interface.h"
#include "flap_control_logic.h"
#include "motor_driver_interface.h"
#include "position_feedback.h"
#include "status_indication.h"
#include "error_handling.h"
#include "configuration_data.h"
#include <stdio.h>
#include <stdint.h>

int main(void) {
    configuration_data_get();
    command_interface_init();
    flap_control_logic_init();
    motor_driver_interface_init();
    position_feedback_init();
    status_indication_init();
    error_handling_init();

    // Main loop stub
    while (1) {
        command_t cmd = command_interface_get_valid_command();
        if (cmd.valid_command_flag) {
            flap_control_logic_update_target(cmd.target_position);
            command_interface_clear_flag();
        }
        flap_control_logic_periodic();
        // Add any other required cycles (status update, error check, etc.)
        // stub: break after 1st loop for demonstration
        break;
    }
    printf("System Halted.\n");
    return 0;
}
