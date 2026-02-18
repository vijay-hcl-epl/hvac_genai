#include "flap_position_control.h"
#include "feedback_acquisition.h"
#include "motor_actuation.h"
#include "status_indication.h"

static int target_position = -1;
static int move_in_progress = 0;

void process_new_command(int cmd) {
    // Set target position
    if (cmd < 0 || cmd > 5) return;
    int current_pos = get_current_position();
    if (current_pos == cmd) return;
    target_position = cmd;
    move_in_progress = 1;
    // Start movement
    if (target_position > current_pos)
        actuate_motor(1); // 1 = Forward (open)
    else
        actuate_motor(0); // 0 = Reverse (close)
}

void check_move_complete(void) {
    if (!move_in_progress) return;
    int current_pos = get_current_position();
    if (current_pos == target_position || current_pos == POSITION_INVALID) {
        stop_motor();
        move_in_progress = 0;
        update_status_leds(current_pos);
    }
}
