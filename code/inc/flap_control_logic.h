#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

// Possible states for flap control logic
typedef enum {
    FLAP_STATE_IDLE,
    FLAP_STATE_MOVING,
    FLAP_STATE_ARRIVED,
    FLAP_STATE_ERROR
} flap_state_t;

// Initialize the flap control logic
void flap_control_logic_init(void);
// Process the flap logic loop (call periodically or on relevant event)
void flap_control_logic_process(void);
// Get the current state (idle, moving, arrived, error)
flap_state_t flap_control_logic_state(void);
// For testing: get last error code
uint8_t flap_control_last_error(void);

#endif // FLAP_CONTROL_LOGIC_H
