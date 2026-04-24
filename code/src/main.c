#include "uart_cmd_handler.h"
#include "position_status_monitor.h"
#include "flap_control_logic.h"
#include "led_status_handler.h"
#include <stdio.h>

int main(void) {
    uart_cmd_init();
    position_status_init();
    flap_control_init();
    led_status_init();

    // Simple simulated main loop
    while (1) {
        position_status_periodic_task();
        int position = position_status_get();
        bool fault = (position_status_get_status() == POS_STATUS_OUT_OF_RANGE);
        led_status_update(position, fault);
        if (fault) {
            flap_control_is_fault();
        }
        // Simulate receiving UART
        // Example: uart_cmd_receive_char('S');
        //         uart_cmd_receive_char('E');
        //         uart_cmd_receive_char('T');
        //         uart_cmd_receive_char(' ');
        //         uart_cmd_receive_char('9');
        //         uart_cmd_receive_char('0');
        //         uart_cmd_receive_char('\n');
        // int target;
        // if (uart_cmd_issue_command(&target)) {
        //     flap_control_start_move(target);
        // }
        // if (flap_control_is_at_target()) {
        //     flap_control_stop();
        // }
        break;
    }

    return 0;
}
