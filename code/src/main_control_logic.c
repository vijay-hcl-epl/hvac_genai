#include "main_control_logic.h"
#include "motor_actuator.h"
#include "position_feedback.h"
#include "indicator_control.h"

// State enums
typedef enum { STATE_IDLE, STATE_MOVING, STATE_ERROR } ctrl_state_t;
static ctrl_state_t ctrl_state = STATE_IDLE;
static uint8_t target_position = 0xFF;
static uint8_t actual_position = 0xFF;
static bool move_in_progress = false;

void main_control_logic_init(void) {
  ctrl_state = STATE_IDLE;
  target_position = 0xFF;
  actual_position = 0xFF;
  move_in_progress = false;
}

void main_control_logic_on_position_cmd(uint8_t logical_position) {
  if (ctrl_state == STATE_ERROR) return;
  if (logical_position == actual_position) return;
  target_position = logical_position;
  move_in_progress = true;
  ctrl_state = STATE_MOVING;
  motor_actuator_move();
}

void main_control_logic_on_position_feedback(uint8_t logical_position, int adc_val, bool in_range) {
  actual_position = logical_position;
  if (!in_range) {
    main_control_logic_on_error();
    return;
  }
  if (move_in_progress && actual_position == target_position) {
    motor_actuator_stop();
    move_in_progress = false;
    ctrl_state = STATE_IDLE;
  }
  indicator_control_update(actual_position, ctrl_state);
}

void main_control_logic_periodic(void) {
  // In this stub, just poll feedback
  position_feedback_poll();
}

void main_control_logic_on_error(void) {
  ctrl_state = STATE_ERROR;
  motor_actuator_stop();
  indicator_control_update(actual_position, STATE_ERROR);
}
