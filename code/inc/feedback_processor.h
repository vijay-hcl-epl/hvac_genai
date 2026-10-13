/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation and position mapping.
 *
 * Software Unit : Feedback Processor
 * Traces        : SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *                 SWE-REQ-028, SWE-REQ-030
 * Platform      : STM32F407G-DISC1, STM32 HAL, 12-bit ADC
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

/** ADC valid range boundaries (12-bit ADC: 0–4095) */
#define FB_ADC_MIN   ((uint16_t)0U)
#define FB_ADC_MAX   ((uint16_t)4095U)

/** Position boundary thresholds – static mapping table
 *  Each position zone is defined by [low, high] ADC counts.
 *  Traces: SWE-REQ-027, SWE-REQ-030
 */
#define FB_NUM_POSITIONS  ((uint8_t)5U)

/** Feedback processor states */
typedef enum
{
    FB_STATE_INIT    = 0U,
    FB_STATE_READY,
    FB_STATE_INVALID
} FeedbackState_t;

/** Feedback result */
typedef struct
{
    uint16_t       rawAdc;      /**< Latest raw ADC reading */
    uint8_t        position;    /**< Mapped logical position (0..4) */
    uint8_t        valid;       /**< 1 = valid, 0 = invalid */
    FeedbackState_t state;
} FeedbackData_t;

/**
 * @brief Initialise the feedback processor.
 * Traces: SWE-REQ-020
 */
void FeedbackProcessor_Init(void);

/**
 * @brief Acquire a new ADC sample, validate and map to position.
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017
 */
void FeedbackProcessor_Update(void);

/**
 * @brief Get the current mapped position.
 * @param[out] pPosition  Pointer to receive the position (0..4).
 * @return 1 if last reading is valid, 0 otherwise.
 * Traces: SWE-REQ-010, SWE-REQ-027
 */
uint8_t FeedbackProcessor_GetPosition(uint8_t *pPosition);

#endif /* FEEDBACK_PROCESSOR_H */
