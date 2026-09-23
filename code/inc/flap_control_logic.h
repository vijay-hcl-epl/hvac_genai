/**
 * @file    flap_control_logic.h
 * @brief   Flap Control Logic software unit – header.
 *
 * Decides when motor movement is necessary by comparing the latest
 * user command with the current feedback position.  Manages the
 * IDLE / MOVING / TARGET_REACHED / FAULT state machine.
 *
 * Traceability:
 *   SWE-REQ-004  – Drive motor toward commanded position.
 *   SWE-REQ-005  – Cease actuation on target reached.
 *   SWE-REQ-006  – Ignore movement if target == current.
 *   SWE-REQ-023  – Compare command vs. feedback, move if needed.
 *   SWE-REQ-024  – Confirm target by equivalence of mapped ADC & cmd.
 *   SWE-REQ-031  – Identify out-of-range feedback as error.
 *   SWE-REQ-033  – Respond promptly to valid command.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

/* ---- Public Types --------------------------------------------------- */

/** @brief Flap control states (LLD SM). */
typedef enum
{
    FLAP_STATE_IDLE           = 0U,
    FLAP_STATE_MOVING,
    FLAP_STATE_TARGET_REACHED,
    FLAP_STATE_FAULT
} FlapControlState_t;

/* ---- Public API ----------------------------------------------------- */

/**
 * @brief  Initialise flap control logic (state → IDLE).
 *         [SWE-REQ-020]
 */
void FlapControl_Init(void);

/**
 * @brief  Main task – call cyclically from the super-loop.
 *         Reads latest command, reads feedback, decides on motor action,
 *         updates LEDs.
 *         [SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024]
 */
void FlapControl_Run(void);

/**
 * @brief  Return current flap-control state (for external observation / test).
 *         [SWE-REQ-040]
 */
FlapControlState_t FlapControl_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
