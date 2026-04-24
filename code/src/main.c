#include "hw_abstraction.h"
#include "flap_control.h"
#include "user_cmd.h"
#include "led_status.h"

int main(void) {
    hw_init();
    flap_control_init();
    led_status_init();
    while(1) {
        user_cmd_process_uart();
        flap_control_update();
        uint8_t pos = flap_control_get_position();
        led_status_update_position(pos);
        // Insert periodic delay as required
    }
    return 0;
}
