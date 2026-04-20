#include "flap_control.h"
#include "motor_control.h"
#include "led_indication.h"
#include "config_calib.h"
static flap_state_t flap_state = FLAP_IDLE;
static uint8_t target_position = 0;
static uint8_t current_position = 0;
static bool move_pending = false;
void request_flap_move(uint8_t pos) {
    if (flap_state != FLAP_IDLE) return;
    target_position = pos;
    if (current_position != target_position) {
        start_motor((target_position > current_position)?1:0, get_config_param(MAX_PWM_ID));
        flap_state = FLAP_MOVING;
        move_pending = true;
    }
}
void feedback_update(uint8_t sensed_pos, bool errorflag) {
    if (errorflag) {
        flap_state = FLAP_ERROR;
        set_error_led();
        stop_motor();
        move_pending = false;
        return;
    }
    current_position = sensed_pos;
    if (flap_state == FLAP_MOVING) {
        if (current_position == target_position) {
            stop_motor();
            flap_state = FLAP_IDLE;
            update_position_led(current_position);
            move_pending = false;
        }
    }
}
