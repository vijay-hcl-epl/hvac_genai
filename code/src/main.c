#include "input_handler.h"
#include "position_sensor_interface.h"
#include "control_logic.h"
#include "status_indicator.h"
#include <stdio.h>

int main(void) {
    control_logic_init();
    int user_input = 75; // Example user input
    if (input_handler_validate(user_input)) {
        control_logic_command(user_input);
        status_indicator_update(LED_MOVING);
        while (!control_logic_is_at_target()) {
            int pos = position_sensor_read();
            control_logic_update_position(pos);
        }
        status_indicator_update(LED_AT_TARGET);
    } else {
        status_indicator_update(LED_ERROR);
        printf("Invalid input!\n");
    }
    return 0;
}
