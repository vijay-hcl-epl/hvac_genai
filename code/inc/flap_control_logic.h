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

/**
 * @brief Flap control states.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-031
 */
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
 * Traces: SWE-REQ-020
 */
void FlapControl_Init(void);

/**
 * @brief Issue a movement command toward a target position.
 *
 * Compares target with current feedback; moves only if different (SWE-REQ-006).
 *
 * @param[in] target_pos  Target flap position (0..4).
 *
 * Traces: SWE-REQ-004, SWE-REQ-006, SWE-REQ-023
 */
void FlapControl_IssueMovementCmd(uint8_t target_pos);

/**
 * @brief Run one cycle of the flap control state machine.
 *
 * Reads feedback, decides motor action, updates LEDs.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 */
void FlapControl_Run(void);

/**
 * @brief Get current flap control state.
 *
 * @return FlapState_t  Current state.
 */
FlapState_t FlapControl_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
