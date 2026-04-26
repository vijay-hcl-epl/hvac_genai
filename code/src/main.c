#include "input_management.h"
#include "flap_control_logic.h"
#include "position_sensing_feedback.h"
#include "status_indication.h"
#include <stdio.h>

int main(void) {
    input_mgmt_init();
    flap_control_init();
    position_sensing_init();
    status_indication_init();
    indicate_power_on();

    while (1) {
        // Main control loop
        flap_control_main();
        // Simulate UART RX (stub):
        // char rx[] = "2\n";
        // process_uart_rx(rx, strlen(rx));
        // Add OS/RTOS wait or delay as required
    }
    return 0;
}
