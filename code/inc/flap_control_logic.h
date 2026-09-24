/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – movement decision, state management.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

/** Flap control state enumeration */
typedef enum
{
    FLAP_STATE_IDLE           = 0U,
    FLAP_STATE_MOVING         = 1U,
    FLAP_STATE_TARGET_REACHED = 2U,
    FLAP_STATE_FAULT          = 3U
} FlapState_t;

/**
 * @brief Initialise flap control logic internal state.
 *
 * Sets state to IDLE, clears target and current position.
 *
 * Traces: SWE-REQ-020
 */
void FlapControl_Init(void);

/**
 * @brief Issue a new movement command.
 *
 * If target_pos differs from the current feedback position, transitions
 * to MOVING and drives the motor.  If equal, command is ignored (SWE-REQ-006).
 *
 * @param target_pos  Desired logical flap position (0..4).
 *
 * Traces: SWE-REQ-004, SWE-REQ-006, SWE-REQ-023, SWE-REQ-033
 */
void FlapControl_SetTarget(uint8_t target_pos);

/**
 * @brief Periodic / cyclic task – evaluate feedback, manage state transitions.
 *
 * Reads current position from Feedback Processor, compares with target.
 * On match → stops motor, updates LEDs, transitions to TARGET_REACHED.
 * On feedback fault → enters FAULT, stops motor.
 *
 * Traces: SWE-REQ-005, SWE-REQ-008, SWE-REQ-024, SWE-REQ-025, SWE-REQ-031
 */
void FlapControl_Run(void);

/**
 * @brief Return the current flap control state.
 *
 * @return Current FlapState_t value.
 */
FlapState_t FlapControl_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
