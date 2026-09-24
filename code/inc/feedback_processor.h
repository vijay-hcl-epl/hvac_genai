/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation, and position mapping.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Reads the potentiometer ADC channel, validates the raw value against
 * static boundaries, and maps it to a logical flap position via a fixed
 * lookup table.  No dynamic allocation, no self-learning.
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

/** ADC resolution (12-bit on STM32F407) */
#define FB_ADC_MAX_VALUE       (4095U)

/** Number of defined flap positions */
#define FB_NUM_POSITIONS       (5U)

/** Validity flag values */
#define FB_VALID               (1U)
#define FB_INVALID             (0U)

/** Feedback processor states */
typedef enum
{
    FB_STATE_INIT    = 0U,
    FB_STATE_READY   = 1U,
    FB_STATE_INVALID = 2U
} FbState_t;

/** Feedback result structure */
typedef struct
{
    uint8_t  position;    /**< Mapped logical position (1..5), 0 if invalid */
    uint8_t  valid;       /**< FB_VALID or FB_INVALID */
    uint16_t rawAdc;      /**< Last raw ADC reading */
    FbState_t state;      /**< Current module state */
} FbResult_t;

/**
 * @brief Initialise the feedback processor (ADC config, clear state).
 *        [SWE-REQ-020]
 */
void FeedbackProcessor_Init(void);

/**
 * @brief Acquire a new ADC sample, validate, and update mapped position.
 *        [SWE-REQ-010, SWE-REQ-011, SWE-REQ-017]
 */
void FeedbackProcessor_Update(void);

/**
 * @brief Get the current feedback result (position + validity).
 * @return FbResult_t
 *         [SWE-REQ-010, SWE-REQ-027]
 */
FbResult_t FeedbackProcessor_GetPosition(void);

#endif /* FEEDBACK_PROCESSOR_H */
