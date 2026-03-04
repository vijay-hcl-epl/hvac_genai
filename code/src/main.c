#include "command_interpreter.h"
#include "flap_control.h"
#include "motor_control.h"
#include "feedback_acquisition.h"
#include "status_indication.h"
#include "hw_interface.h"

int main(void) {
    hw_interface_init();
    command_interpreter_init();
    flap_control_init();
    motor_control_init();
    feedback_acquisition_init();
    status_indication_init();

    while(1) {
        uint8_t cmd = uart_read();
        accept_command(cmd);
    }
    return 0;
}
