#include "motor_actuator.h"
#include <stdbool.h>

static bool initialized = false;

void motor_actuator_init(void) {
  initialized = true;
  // HW: Set output to OFF
}

void motor_actuator_move(void) {
  if (!initialized) return;
  // HW: Set output to ON
}

void motor_actuator_stop(void) {
  if (!initialized) return;
  // HW: Set output to OFF
}
