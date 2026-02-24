#include "flap_position_controller.h"
#include "motor_controller.h"
#include "position_feedback_reader.h"
#include "status_led_manager.h"

#include <stdint.h>
#include <stdbool.h>

static uint16_t target_position = 0;
static uint16_t actual_position = 0;
static int16_t position_error = 0;
static bool movement_active = false;
#define POSITION_TOLERANCE 1

void flap_position_controller_init(void) {
    target_position = 0;
    actual_position = 0;
    position_error = 0;
    movement_active = false;
}

void set_flap_target(uint16_t position) {
    target_position = position;
    notify_position_update(get_position());
}

void notify_position_update(uint16_t new_actual_position) {
    actual_position = new_actual_position;
    if (actual_position > 3) {
        set_led_status(LED_ERROR, true);
        set_motor_state(MOTOR_DIRECTION_NONE, false);
        movement_active = false;
        return;
    }
    if (actual_position == target_position) {
        set_motor_state(MOTOR_DIRECTION_NONE, false);
        set_led_status(LED_POWER, true);
        set_led_status(LED_ERROR, false);
        set_led_status(LED_FLAP_POS_0, actual_position == 0);
        set_led_status(LED_FLAP_POS_1, actual_position == 1);
        set_led_status(LED_FLAP_POS_2, actual_position == 2);
        set_led_status(LED_FLAP_POS_3, actual_position == 3);
        movement_active = false;
    } else {
        position_error = (int16_t)target_position - (int16_t)actual_position;
        if (position_error > 0) {
            set_motor_state(MOTOR_DIRECTION_FORWARD, true);
            movement_active = true;
        } else if (position_error < 0) {
            set_motor_state(MOTOR_DIRECTION_REVERSE, true);
            movement_active = true;
        }
    }
}
