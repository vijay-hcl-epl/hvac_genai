/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – movement decision, state management.
 *
 * Software Unit : Flap Control Logic
 * Traces        : SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *                 SWE-REQ-024, SWE-REQ-031
 * Platform      : STM32F407G-DISC1
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

/** Flap control states */
typedef enum
{
    FLAP_STATE_IDLE           = 0U,
    FLAP_STATE_MOVING,
    FLAP_STATE_TARGET_REACHED,
    FLAP_STATE_FAULT
} FlapControlState_t;

/** Flap control data */
typedef struct
{
    uint8_t            currentPos;   /**< Last confirmed position from feedback */
    uint8_t            targetPos;    /**< Commanded target position */
    uint8_t            inMotion;     /**< 1 = motor active, 0 = idle */
    FlapControlState_t state;
} FlapControlData_t;

/**
 * @brief Initialise flap control logic.
 * Traces: SWE-REQ-020
 */
void FlapControl_Init(void);

/**
 * @brief Run one cycle of the flap control state machine.
 *        Reads command, reads feedback, drives motor, updates LEDs.
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024
 */
void FlapControl_Run(void);

/**
 * @brief Get current flap control state (for testability / LED handler).
 * @return Current FlapControlState_t.
 * Traces: SWE-REQ-040
 */
FlapControlState_t FlapControl_GetState(void);

#endif /* FLAP_CONTROL_LOGIC_H */
