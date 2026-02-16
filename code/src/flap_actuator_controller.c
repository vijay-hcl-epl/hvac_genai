#include "flap_actuator_controller.h"
#include "motor_control_unit.h"
#include "position_monitoring_unit.h"
#include "led_indication.h"
#include "uart_command_handler.h"

static flap_ctrl_state_t ctrl_state = CTRL_IDLE;
static int current_position = 0;
static int target_position = 0;
static bool command_in_progress = false;
static bool error_flag = false;

void flap_actuator_controller_init(void) {
    ctrl_state = CTRL_IDLE;
    command_in_progress = false;
    error_flag = false;
    current_position = get_current_position();
    target_position = current_position;
}

void process_uart_command(int cmd) {
    if ((ctrl_state == CTRL_IDLE) && (!command_in_progress)) {
        if ((cmd < 0) || (cmd > 100)) {
            error_flag = true;
            ctrl_state = CTRL_ERROR;
            return;
        }
        if (cmd == current_position) { return; }
        target_position = cmd;
        command_in_progress = true;
        ctrl_state = CTRL_PROCESSING;
    }
}

void flap_actuator_controller_task(void) {
    switch (ctrl_state) {
        case CTRL_IDLE:
            if (is_command_ready()) {
                int cmd = get_parsed_command();
                process_uart_command(cmd);
            }
            break;
        case CTRL_PROCESSING:
            if (current_position < target_position) {
                move_motor_to(target_position, MOTOR_DIR_FWD);
                ctrl_state = CTRL_WAIT_MOVEMENT;
            } else if (current_position > target_position) {
                move_motor_to(target_position, MOTOR_DIR_REV);
                ctrl_state = CTRL_WAIT_MOVEMENT;
            } else {
                ctrl_state = CTRL_IDLE;
                command_in_progress = false;
            }
            break;
        case CTRL_WAIT_MOVEMENT:
            current_position = get_current_position();
            if (current_position == target_position) {
                stop_motor();
                set_led_position(current_position);
                ctrl_state = CTRL_IDLE;
                command_in_progress = false;
            } else if (get_position_status() != POSITION_OK) {
                stop_motor();
                error_flag = true;
                ctrl_state = CTRL_ERROR;
            }
            break;
        case CTRL_ERROR:
            set_led_status(false);
            command_in_progress = false;
            break;
        default:
            break;
    }
}

flap_ctrl_state_t get_flap_ctrl_state(void) {
    return ctrl_state;
}

bool get_ctrl_error_flag(void) {
    return error_flag;
}

void clear_ctrl_error(void) {
    ctrl_state = CTRL_IDLE;
    error_flag = false;
}
