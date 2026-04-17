#include "position_control.h"
#include "motor_driver_if.h"
#include "adc_interface.h"
#include "led_status.h"
#include "error_handling.h"
#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5
static uint8_t target_pos = 0;
static uint8_t actual_pos = 0;
static uint8_t move_state = 0; // 0:IDLE 1:MOVING 2:ERROR
static bool busy = false;
void position_control_init(void) { target_pos = 0; actual_pos = 0; move_state = 0; busy = false; }
bool position_control_set_target(uint8_t pos)
{
    if (busy || pos > FLAP_POS_MAX) return false;
    target_pos = pos;
    busy = true; move_state = 1;
    return true;
}
void position_control_execute(void)
{
    if (!busy) return;
    actual_pos = adc_interface_get_position();
    if (error_handling_has_error()) {
        busy = false; move_state = 2; return;
    }
    if (actual_pos == target_pos) {
        motor_driver_if_stop();
        led_status_update_position(actual_pos);
        busy = false; move_state = 0;
    } else {
        motor_driver_if_drive(target_pos, actual_pos);
        // Stay in MOVING until target reached
    }
}
uint8_t position_control_get_actual(void) { return actual_pos; }
uint8_t position_control_get_state(void) { return move_state; }
