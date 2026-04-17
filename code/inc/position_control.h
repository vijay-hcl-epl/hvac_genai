#ifndef POSITION_CONTROL_H
#define POSITION_CONTROL_H
#include <stdint.h>
#include <stdbool.h>
// Called at power-up
void position_control_init(void);
// Pass new valid target position (0–5); returns true if accepted.
bool position_control_set_target(uint8_t pos);
// Should be called in main loop
void position_control_execute(void);
// Gets last known actual position (0–5)
uint8_t position_control_get_actual(void);
// Gets current movement state (0:IDLE 1:MOVING 2:ERROR)
uint8_t position_control_get_state(void);
#endif
