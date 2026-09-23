/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – movement decision, state management.
 *
 * Software Unit: Flap Control Logic
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

/** Flap Control states per LLD state machine */
typedef enum
{
    FLAPCTRL_STATE_IDLE           = 0U,
    FLAPCTRL_STATE_MOVING         = 1U,
    FLAPCTRL_STATE_TARGET_REACHED = 2U,
    FLAPCTRL_STATE_FAULT          = 3U
} FlapControlState_t;

/**
 * @brief Initialise the Flap Control Logic unit.
 *        Sets state to IDLE, clears commanded position.
 *        [SWE-REQ-020]
 */
void FlapControlLogic_Init(void);

/**
 * @brief Issue a movement command to the flap.
 * @param target_pos  Target position (1..5).
 *        Compares with current feedback; initiates move only if different.
 *        [SWE-REQ-004, SWE-REQ-006, SWE-REQ-023]
 */
void FlapControlLogic_IssueMovementCmd(uint8_t target_pos);

/**
 * @brief Periodic task – evaluates feedback, manages state transitions,
 *        drives motor and LED accordingly.
 *        [SWE-REQ-005, SWE-REQ-024, SWE-REQ-031]
 */
void FlapControlLogic_Run(void);

/**
 * @brief Get current control state.
 * @return FlapControlState_t
 */
FlapControlState_t FlapControlLogic_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
