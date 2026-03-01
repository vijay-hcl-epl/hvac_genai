#include "motor_driver.h"
#include <stdbool.h>
static bool active_signal_flag = false;
static int last_dir = 0;
void motor_driver_init(void) { active_signal_flag = false; }
void motor_move(int direction) {
    // HW GPIO/PWM: direction > 0 = CW, < 0 = CCW
    active_signal_flag = true;
    last_dir = direction;
    // (Stub: actual HW signaling omitted)
}
bool motor_is_active(void) { return active_signal_flag; }
void motor_stop(void) { active_signal_flag = false; }
