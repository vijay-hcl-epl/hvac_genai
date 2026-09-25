/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – Decides movement, manages current/target state.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 * Platform: STM32F407G-DISC1
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

/** Flap control states */
typedef enum
{
    FLAP_STATE_IDLE = 0U,
    FLAP_STATE_MOVING,
    FLAP_STATE_TARGET_REACHED,
    FLAP_STATE_FAULT
} flap_state_t;

/**
 * @brief Initialise flap control logic internal state.
 */
void flap_control_init(void);

/**
 * @brief Issue a new target position command.
 * @param target_pos  Desired position (1–5).
 */
void flap_control_set_target(uint8_t target_pos);

/**
 * @brief Run the flap control state machine.
 *        Reads feedback, drives motor, updates LEDs as needed.
 *        Call periodically from the main loop.
 */
void flap_control_update(void);

/**
 * @brief Get the current flap control state.
 * @return Current flap_state_t value.
 */
flap_state_t flap_control_get_state(void);

#endif /* FLAP_CONTROL_LOGIC_H */
