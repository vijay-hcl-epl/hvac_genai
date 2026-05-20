#include "main_control_logic.h"
#include "motor_actuator.h"
#include "indicator_control.h"
#include "position_feedback.h"

static int target_position;
static int actual_position;

void main_control_process_command(int target) {
    if (target != actual_position) {
        target_position = target;
        motor_actuator_on();
    }
}

void main_control_update_feedback(int actual) {
    actual_position = actual;
    if (actual_position == target_position) {
        motor_actuator_off();
    }
}

void main_control_handle_error(void) {
    motor_actuator_off();
}
