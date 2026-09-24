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

/** ADC valid range boundaries (12-bit ADC: 0..4095) */
#define FB_ADC_MIN         (0U)
#define FB_ADC_MAX         (4095U)

/** Feedback validity codes */
#define FB_VALID           (1U)
#define FB_INVALID         (0U)

/**
 * @brief Initialise the feedback processor.
 *
 * Resets internal ADC sample, mapped position and validity flag.
 *
 * Traces: SWE-REQ-020
 */
void FeedbackProcessor_Init(void);

/**
 * @brief Acquire a new ADC sample and map it to a logical flap position.
 *
 * Reads the potentiometer ADC channel via HAL, validates the raw value
 * against boundaries, and performs a static table lookup to determine the
 * logical position.  Sets internal validity accordingly.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027
 */
void FeedbackProcessor_Update(void);

/**
 * @brief Get the latest mapped position and its validity.
 *
 * @param[out] p_position  Pointer to receive logical position (0..4).
 * @param[out] p_valid     Pointer to receive validity (FB_VALID / FB_INVALID).
 *
 * Traces: SWE-REQ-010, SWE-REQ-030
 */
void FeedbackProcessor_GetPosition(uint8_t *p_position, uint8_t *p_valid);

#endif /* FEEDBACK_PROCESSOR_H */
