/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – movement decision, state management.
 *
 * Software Unit : Flap Control Logic
 * Traceability  : SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *                 SWE-REQ-024, SWE-REQ-031
 */
#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

/* Control-logic states (LLD §3) */
typedef enum
{
    FLAPCTRL_STATE_IDLE           = 0U,
    FLAPCTRL_STATE_MOVING         = 1U,
    FLAPCTRL_STATE_TARGET_REACHED = 2U,
    FLAPCTRL_STATE_FAULT          = 3U
} FlapCtrl_State_t;

/**
 * @brief Initialise flap control logic (IDLE, motor off).
 * Trace: SWE-REQ-020 (via System Init)
 */
void FlapCtrl_Init(void);

/**
 * @brief Issue a movement command (target position).
 *        If target == current, movement is suppressed (SWE-REQ-006).
 * Trace: SWE-REQ-004, SWE-REQ-006, SWE-REQ-023
 *
 * @param target_pos  Desired flap position (0..4).
 */
void FlapCtrl_IssueMovementCmd(uint8_t target_pos);

/**
 * @brief Periodic/event-driven run step – reads feedback, drives motor,
 *        updates LEDs, detects faults.
 * Trace: SWE-REQ-004, SWE-REQ-005, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 */
void FlapCtrl_Run(void);

/**
 * @brief Get the current control-logic state.
 * Trace: SWE-REQ-039 (testability)
 *
 * @return Current FlapCtrl_State_t value.
 */
FlapCtrl_State_t FlapCtrl_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
