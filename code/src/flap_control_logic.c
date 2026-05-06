#include "flap_control_logic.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"
#include <stdint.h>
#include <stdbool.h>

static uint8_t target_position = 0xFF;
static uint8_t current_position = 0xFF;
static bool motion_in_progress = false;
static bool error_flag = false;

void flap_control_init(void) {
    target_position = 0xFF;
    current_position = 0xFF;
    motion_in_progress = false;
    error_flag = false;
}

void flap_control_event(void) {
    uint8_t cmd;
    bool cmd_valid;
    uint8_t fb_pos;
    bool fb_valid;

    if (!command_parser_get_latest_command(&cmd, &cmd_valid)) return;
    if (!feedback_processor_get_position(&fb_pos, &fb_valid)) return;
    
    current_position = fb_pos;
    if (!fb_valid) {
        if (!error_flag) {
            motor_stop();
            led_indicate_error();
            error_flag = true;
        }
        motion_in_progress = false;
        return;
    }
    if (!cmd_valid || cmd == current_position) {
        motor_stop();
        motion_in_progress = false;
        return;
    }
    if (cmd != target_position) {
        target_position = cmd;
        if (cmd > current_position) {
            motor_drive(MOTOR_DIR_OPEN, true);
        } else {
            motor_drive(MOTOR_DIR_CLOSE, true);
        }
        motion_in_progress = true;
    }
    // Check if reached
    if (motion_in_progress && (current_position == target_position)) {
        motor_stop();
        motion_in_progress = false;
        led_set_position(current_position);
    }
}
