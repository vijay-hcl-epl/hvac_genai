/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation and position mapping.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

/** Number of logical flap positions */
#define FB_NUM_POSITIONS   (5U)

/** ADC resolution: 12-bit → max value 4095 */
#define FB_ADC_MAX         (4095U)

/** Boundary tolerance for ADC mapping (counts) */
#define FB_ADC_TOLERANCE   (50U)

/**
 * @brief Feedback data returned to caller.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011
 */
typedef struct
{
    uint8_t position;   /**< Mapped logical position (0..FB_NUM_POSITIONS-1) */
    uint8_t valid;      /**< 1 = position is valid, 0 = invalid / out-of-range */
} FeedbackData_t;

/**
 * @brief Initialise the feedback processor.
 *
 * Traces: SWE-REQ-020
 */
void FeedbackProcessor_Init(void);

/**
 * @brief Acquire a new ADC sample, validate and map to logical position.
 *
 * Reads ADC channel via STM32 HAL, applies boundary check (SWE-REQ-011),
 * performs static table lookup (SWE-REQ-027, SWE-REQ-028).
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027
 */
void FeedbackProcessor_Update(void);

/**
 * @brief Get current mapped position and validity.
 *
 * @return FeedbackData_t  Current feedback data.
 *
 * Traces: SWE-REQ-010, SWE-REQ-030
 */
FeedbackData_t FeedbackProcessor_GetPosition(void);

#endif /* FEEDBACK_PROCESSOR_H */
