#include "uart_handler.h"
#include "feedback_processing.h"
#include "motor_driver.h"
#include "status_indication.h"
#include "error_handling.h"
#include "flap_control_logic.h"
int main(void) {
    uart_handler_init();
    feedback_processing_init();
    motor_driver_init();
    status_indication_init();
    error_handling_init();
    flap_control_init();
    // Main loop
    while(1) {
        flap_control_event();
        // Other unit polling, error check, stub
    }
    return 0;
}
