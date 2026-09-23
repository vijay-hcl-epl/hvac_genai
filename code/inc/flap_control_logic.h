/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic Software Unit – Header
 *
 * Decides when to move the actuator flap by comparing the commanded
 * target position with the current feedback position, and orchestrates
 * Motor Driver and LED Status Handler accordingly.
 *
 * Traceability:
 *   SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *   SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

/**
 * @brief Flap Control Logic states per LLD state machine.
 *        {IDLE, MOVING, TARGET_REACHED, FAULT}
 */
typedef enum
{
    FLAP_STATE_IDLE           = 0U,
    FLAP_STATE_MOVING         = 1U,
    FLAP_STATE_TARGET_REACHED = 2U,
    FLAP_STATE_FAULT          = 3U
} FlapControlState_t;

/**
 * @brief Motor movement direction used internally.
 *        [SWE-REQ-004, SWE-REQ-007]
 */
typedef enum
{
    FLAP_DIR_NONE    = 0U,
    FLAP_DIR_FORWARD = 1U,
    FLAP_DIR_REVERSE = 2U
} FlapDirection_t;

/**
 * @brief Initialise the Flap Control Logic unit.
 *        Must be called once at startup.
 *        [SWE-REQ-020]
 */
void FlapControlLogic_Init(void);

/**
 * @brief Main task dispatcher for flap control.
 *        Reads latest command & feedback, decides on motor action.
 *        Call cyclically from main loop.
 *        [SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024]
 */
void FlapControlLogic_Run(void);

/**
 * @brief Retrieve the current state of the flap control state machine.
 * @return FlapControlState_t
 */
FlapControlState_t FlapControlLogic_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
