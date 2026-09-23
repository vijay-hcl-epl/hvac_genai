/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation, and position mapping.
 *
 * Software Unit: Feedback Processor
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (ADC1)
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

/** ADC boundaries for validity check (12-bit ADC: 0..4095) */
#define FEEDBACK_ADC_MIN        ((uint16_t)100U)
#define FEEDBACK_ADC_MAX        ((uint16_t)3900U)

/** Number of discrete flap positions */
#define FEEDBACK_NUM_POSITIONS  ((uint8_t)5U)

/** Feedback Processor states per LLD */
typedef enum
{
    FBPROC_STATE_INIT    = 0U,
    FBPROC_STATE_READY   = 1U,
    FBPROC_STATE_INVALID = 2U
} FeedbackProcessorState_t;

/** Position result structure */
typedef struct
{
    uint8_t position;   /**< Mapped logical position (1..5), 0 if invalid */
    bool    valid;      /**< true if current reading is valid              */
} FeedbackResult_t;

/**
 * @brief Initialise the Feedback Processor unit.
 *        Configures ADC channel, sets state to INIT.
 *        [SWE-REQ-020]
 */
void FeedbackProcessor_Init(void);

/**
 * @brief Acquire a new ADC sample, validate, and map to logical position.
 *        [SWE-REQ-010, SWE-REQ-011, SWE-REQ-027]
 */
void FeedbackProcessor_Update(void);

/**
 * @brief Get the current mapped position and validity.
 * @return FeedbackResult_t  position + valid flag.
 *         [SWE-REQ-010, SWE-REQ-017]
 */
FeedbackResult_t FeedbackProcessor_GetPosition(void);

#endif /* FEEDBACK_PROCESSOR_H */
