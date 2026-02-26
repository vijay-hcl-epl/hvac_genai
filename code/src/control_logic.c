#include "control_logic.h"
#include "command_handler.h"
#include "position_feedback.h"
#include "motor_driver.h"
#include "led_driver.h"

#include <stdbool.h>

static int target_position = -1;
static bool command_in_progress = false;
static bool error_state = false;

void control_logic_init(void){
    target_position = -1;
    command_in_progress = false;
    error_state = false;
}

void control_logic_execute_cycle(void){
    if(!command_in_progress && command_handler_is_command_pending()){
        int cmd = command_handler_get_command();
        if(cmd >= 0 && cmd <= 5){
            target_position = cmd;
            command_in_progress = true;
        } else {
            // ignore invalid, clear command and return
            command_handler_clear_error();
            return;
        }
    }
    int current_position = position_feedback_get_position();
    if(position_feedback_is_valid()){
        if(command_in_progress && target_position != current_position){
            if(target_position > current_position){
                motor_driver_actuate(MOTOR_FORWARD);
            } else if(target_position < current_position){
                motor_driver_actuate(MOTOR_REVERSE);
            }
        }else if(command_in_progress && target_position == current_position){
            motor_driver_stop();
            led_driver_update(current_position);
            command_in_progress = false;
            command_handler_command_complete();
        }
    } else {
        // Feedback error, stop motor and light error
        motor_driver_stop();
        error_state = true;
        led_driver_signal_error();
        command_in_progress = false;
        command_handler_command_complete();
    }
}

bool control_logic_is_moving(void){
    return command_in_progress;
}

bool control_logic_get_error(void){
    return error_state;
}

void control_logic_command_complete(void){
    command_in_progress = false;
    command_handler_command_complete();
}
