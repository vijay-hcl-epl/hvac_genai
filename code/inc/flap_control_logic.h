/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – movement decision, state management.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *         SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

/** Flap control states. */
typedef enum
{
    FLAP_STATE_IDLE           = 0U,
    FLAP_STATE_MOVING         = 1U,
    FLAP_STATE_TARGET_REACHED = 2U,
    FLAP_STATE_FAULT          = 3U
} FlapState_t;

/**
 * @brief Initialise flap control logic (set IDLE, clear positions).
 *        [SWE-REQ-020]
 */
void FlapControl_Init(void);

/**
 * @brief Cyclic task – reads latest command & feedback, decides on action.
 *        Invokes Motor Driver and LED Status Handler as required.
 *        [SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024]
 */
void FlapControl_Run(void);

/**
 * @brief Return current flap control state.
 * @return Current FlapState_t value.
 *         [SWE-REQ-040]
 */
FlapState_t FlapControl_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
