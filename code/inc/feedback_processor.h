/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation, and position mapping.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *         SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

/** ADC resolution (12-bit on STM32F407). */
#define FB_ADC_MAX_VALUE     ((uint16_t)4095U)

/** Boundary guard – values outside this range are considered invalid. */
#define FB_ADC_LOW_BOUND     ((uint16_t)50U)
#define FB_ADC_HIGH_BOUND    ((uint16_t)4000U)

/**
 * @brief Initialise the feedback processor (ADC channel setup, clear state).
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
 * @param[out] p_position  Logical position (1-5, same encoding as command).
 * @param[out] p_valid     true if latest sample was in range and mapped.
 *        [SWE-REQ-010, SWE-REQ-017]
 */
void FeedbackProcessor_GetPosition(uint8_t *p_position, bool *p_valid);

/**
 * @brief Get the raw ADC value of the last sample (for debug / testability).
 * @return Raw 12-bit ADC value.
 *         [SWE-REQ-039, SWE-REQ-040]
 */
uint16_t FeedbackProcessor_GetRawADC(void);

#endif /* FEEDBACK_PROCESSOR_H */
