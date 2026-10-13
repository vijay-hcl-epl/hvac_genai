/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – movement decision, state management, coordination.
 *
 * Software Unit: Flap Control Logic
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1 (logic only – no direct HW access)
 */
#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

/** Flap Control states per LLD §Flap Control Logic. */
typedef enum
{
    FLAP_STATE_IDLE           = 0U,
    FLAP_STATE_MOVING         = 1U,
    FLAP_STATE_TARGET_REACHED = 2U,
    FLAP_STATE_FAULT          = 3U
} flap_state_t;

/**
 * @brief Initialise Flap Control Logic (IDLE, no target).
 * Traces: SWE-REQ-020
 */
void flap_control_init(void);

/**
 * @brief Issue a new movement command (target position).
 *
 * Compares target with current feedback; starts movement only if different.
 * If feedback is invalid, enters FAULT and stops motor.
 *
 * Traces: SWE-REQ-004, SWE-REQ-006, SWE-REQ-023, SWE-REQ-033
 *
 * @param target_pos  Desired flap position (1..NUM_POSITIONS).
 */
void flap_control_issue_command(uint8_t target_pos);

/**
 * @brief Periodic task – checks feedback, manages state transitions.
 *
 * Called from the main super-loop.  Reads feedback, compares with target,
 * and transitions through MOVING → TARGET_REACHED or FAULT as appropriate.
 *
 * Traces: SWE-REQ-005, SWE-REQ-008, SWE-REQ-023, SWE-REQ-024, SWE-REQ-025, SWE-REQ-031
 */
void flap_control_run(void);

/**
 * @brief Return the current control state.
 */
flap_state_t flap_control_get_state(void);

#endif /* FLAP_CONTROL_LOGIC_H */
