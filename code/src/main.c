#include "init_startup.h"
#include "command_input.h"
#include "feedback_acquisition.h"
#include "flap_position_control.h"
#include "status_indication.h"

int main(void) {
    system_init();
    power_led_on();
    while (init_complete()) {
        int cmd = get_valid_position();
        if (cmd != CMD_INVALID) {
            process_new_command(cmd);
        }
        check_move_complete();
        // ... insert optional wait/event ...
    }
    return 0;
}
