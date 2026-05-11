#include "uart_command_handler.h"
#include "main_control_logic.h"
#include "position_feedback.h"

static void on_uart_command(uint8_t pos, bool valid) {
    main_control_logic_on_cmd(pos, valid);
}
static void on_feedback(uint8_t pos, bool in_range) {
    main_control_logic_on_feedback(pos, in_range);
}

int main(void)
{
    uart_command_handler_init(&on_uart_command);
    main_control_logic_init();
    position_feedback_init(&on_feedback);
    //motor_actuator_init();
    //indicator_control_init();
    while (1) {
        // Simulated main loop
        main_control_logic_run();
        // position_feedback_update(); (call on timer/trigger)
    }
    return 0;
}
