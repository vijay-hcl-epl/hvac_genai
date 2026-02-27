#include "flap_control_logic.h"
#include "user_command_interface.h"
#include "position_feedback.h"
#include "motor_indicator_interface.h"
#include <stdint.h>

// Internal states
static flap_state_t flap_state = FLAP_STATE_IDLE;
static uint8_t last_error = 0;

// Configurable debounce and timeout
#define DEBOUNCE_COUNT 4
#define MOVE_TIMEOUT 50 // cycles (tunable)

static uint8_t debounce_counter = 0;
static uint8_t move_timeout_counter = 0;
static uint8_t target_position = 0xFF;
static bool flap_moving = false;

void flap_control_logic_init(void)
{
    flap_state = FLAP_STATE_IDLE;
    last_error = 0;
    target_position = 0xFF;
    flap_moving = false;
    debounce_counter = 0;
    move_timeout_counter = 0;
}

void flap_control_logic_process(void)
{
    user_command_t cmd = get_user_command();
    position_feedback_t fb = get_position_feedback();
    static uint8_t last_position = 0xFF;
    bool need_move = false;

    if (!cmd.valid || fb.fault) {
        // Invalid or fault: system idle, show error
        motor_drive_request(MOTOR_DIRECTION_NONE, false);
        set_led_state(fb.position_index, true);
        flap_state = fb.fault ? FLAP_STATE_ERROR : FLAP_STATE_IDLE;
        last_error = fb.fault ? 1 : 0;
        flap_moving = false;
        target_position = fb.position_index;
        return;
    }
    if (target_position == 0xFF || !flap_moving) {
        // New command?
        if (cmd.position_index != fb.position_index && cmd.position_index < NUM_FLAP_POSITIONS) {
            target_position = cmd.position_index;
            flap_moving = true;
            move_timeout_counter = MOVE_TIMEOUT;
            flap_state = FLAP_STATE_MOVING;
        } else {
            flap_state = FLAP_STATE_IDLE;
            target_position = fb.position_index;
            flap_moving = false;
        }
    }
    if (flap_moving) {
        if (fb.position_index == target_position) {
            // Arrived!
            motor_drive_request(MOTOR_DIRECTION_NONE, false);
            set_led_state(target_position, false);
            debounce_counter = 0;
            flap_moving = false;
            flap_state = FLAP_STATE_ARRIVED;
            return;
        } else {
            // Need to move: determine direction
            if (--move_timeout_counter == 0) {
                // Timeout
                motor_drive_request(MOTOR_DIRECTION_NONE, false);
                set_led_state(fb.position_index, true);
                flap_state = FLAP_STATE_ERROR;
                last_error = 2;
                flap_moving = false;
                return;
            }
            motor_direction_t dir = (target_position > fb.position_index) ? 
                MOTOR_DIRECTION_FORWARD : MOTOR_DIRECTION_REVERSE;
            motor_drive_request(dir, true);
            set_led_state(fb.position_index, false);
        }
    }
}

flap_state_t flap_control_logic_state(void)
{
    return flap_state;
}

uint8_t flap_control_last_error(void)
{
    return last_error;
}
