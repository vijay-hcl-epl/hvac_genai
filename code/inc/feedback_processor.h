/**
 * @file feedback_processor.h
 * @brief Feedback Processor Software Unit – Header
 *
 * Acquires ADC samples from the potentiometer, validates range,
 * and maps to a logical flap position via a fixed lookup table.
 *
 * Traceability:
 *   SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *   SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief ADC resolution for STM32F407 (12-bit).
 *        [SWE-REQ-017]
 */
#define FEEDBACK_ADC_MAX          (4095U)

/**
 * @brief Number of discrete flap positions mapped from ADC range.
 *        Must match CMD_PARSER_NUM_POSITIONS.
 *        [SWE-REQ-027, SWE-REQ-030, SWE-REQ-038]
 */
#define FEEDBACK_NUM_POSITIONS    (5U)

/**
 * @brief Feedback Processor states per LLD state machine.
 *        {INIT, READY, INVALID}
 */
typedef enum
{
    FB_STATE_INIT    = 0U,
    FB_STATE_READY   = 1U,
    FB_STATE_INVALID = 2U
} FeedbackState_t;

/**
 * @brief Result structure returned by FeedbackProcessor_GetPosition().
 *        [SWE-REQ-010]
 */
typedef struct
{
    uint8_t position;   /**< Mapped logical position (1..NUM_POSITIONS) */
    bool    valid;      /**< true if ADC sample was in valid range       */
} FeedbackResult_t;

/**
 * @brief Initialise the Feedback Processor unit.
 *        Must be called once at startup.
 *        [SWE-REQ-020]
 */
void FeedbackProcessor_Init(void);

/**
 * @brief Acquire a new ADC sample, validate, and update mapped position.
 *        Call cyclically from the main dispatcher.
 *        [SWE-REQ-010, SWE-REQ-011, SWE-REQ-017]
 */
void FeedbackProcessor_Update(void);

/**
 * @brief Retrieve the latest mapped position and validity.
 * @return FeedbackResult_t  position + valid flag
 *         [SWE-REQ-010, SWE-REQ-027]
 */
FeedbackResult_t FeedbackProcessor_GetPosition(void);

#endif /* FEEDBACK_PROCESSOR_H */
