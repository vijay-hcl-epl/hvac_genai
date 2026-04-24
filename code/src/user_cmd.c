#include "user_cmd.h"
#include "hw_abstraction.h"
#include "flap_control.h"
void user_cmd_process_uart(void) {
    uint8_t rx;
    if(hw_uart_read(&rx) > 0) {
        if(rx >= '0' && rx <= '5') {
            flap_control_set_target(rx - '0');
        }
    }
}
