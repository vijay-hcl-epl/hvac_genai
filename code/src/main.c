#include "command_handler.h"
#include "flap_control.h"
#include "feedback_acq.h"
#include "led_indication.h"
#include "motor_control.h"
#include "config_calib.h"
int main(void) {
    set_status_led(true);
    update_feedback();
    update_position_led(get_feedback());
    while (1) {
        if (is_command_ready()) {
            int cmd = get_next_command();
            if (cmd >= 0 && cmd <= 5) {
                request_flap_move((uint8_t)cmd);
            }
        }
        update_feedback();
        // Add delay or low-power idle here
    }
    return 0;
}
