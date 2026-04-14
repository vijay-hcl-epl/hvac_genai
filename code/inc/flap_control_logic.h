#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

// States for flap control
typedef enum {
    FLAP_IDLE,
    FLAP_MOVING,
    FLAP_TARGET_REACHED,
    FLAP_FAULT
} flap_ctrl_state_t;

// API
void flap_control_init(void);
void flap_control_task(void); // Call in main loop
void flap_control_new_command(uint8_t pos, bool valid);
void flap_control_feedback_update(uint8_t pos, bool valid);

#endif // FLAP_CONTROL_LOGIC_H
