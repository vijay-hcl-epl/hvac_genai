#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

// States for logic control
typedef enum {
    FLAP_STATE_IDLE,
    FLAP_STATE_MOVING,
    FLAP_STATE_AT_TARGET,
    FLAP_STATE_ERROR
} flap_state_t;

// API: Init logic
void flap_control_logic_init(void);
// API: Handle validated command
void flap_control_on_valid_position(uint8_t position_idx);
// API: Periodic/control task
void flap_control_logic_task(void);
// API: Expose status for test
flap_state_t flap_control_get_state(void);
uint8_t flap_control_get_position(void);

#endif // FLAP_CONTROL_LOGIC_H
