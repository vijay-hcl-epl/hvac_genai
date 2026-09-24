/**
 * @file flap_control_logic.h
 * @brief Flap Control Logic – movement decision and state management.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Compares commanded position with feedback, decides motor actuation,
 * and coordinates Motor Driver, LED Status Handler, and Feedback Processor.
 * No direct hardware interaction. No dynamic allocation.
 */

#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

/** Flap control states */
typedef enum
{
    FLAP_STATE_IDLE           = 0U,
    FLAP_STATE_MOVING         = 1U,
    FLAP_STATE_TARGET_REACHED = 2U,
    FLAP_STATE_FAULT          = 3U
} FlapState_t;

/** Flap control status structure */
typedef struct
{
    FlapState_t state;             /**< Current control state */
    uint8_t     currentPosition;   /**< Last confirmed position from feedback */
    uint8_t     targetPosition;    /**< Commanded target position */
    uint8_t     inMotion;          /**< 1 = motor active, 0 = stopped */
} FlapStatus_t;

/**
 * @brief Initialise flap control logic (state = IDLE, clear positions).
 *        [SWE-REQ-020]
 */
void FlapControl_Init(void);

/**
 * @brief Issue a new movement command (target position).
 *        If target == current, movement is ignored (SWE-REQ-006).
 * @param targetPos  Desired flap position (1..5)
 *        [SWE-REQ-004, SWE-REQ-006, SWE-REQ-023]
 */
void FlapControl_SetTarget(uint8_t targetPos);

/**
 * @brief Run one cycle of the control logic.
 *        Reads feedback, compares with target, drives motor/LED accordingly.
 *        Must be called cyclically from main loop.
 *        [SWE-REQ-004, SWE-REQ-005, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031]
 */
void FlapControl_Run(void);

/**
 * @brief Retrieve current flap control status.
 * @return FlapStatus_t
 */
FlapStatus_t FlapControl_GetStatus(void);

#endif /* FLAP_CONTROL_LOGIC_H */
