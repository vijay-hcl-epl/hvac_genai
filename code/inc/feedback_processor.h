/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation, and position mapping.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 * Platform: STM32F407G-DISC1 / STM32 HAL / ADC1
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

/** ADC valid range boundaries (12-bit ADC, 0–4095) */
#define FB_ADC_MIN              (0U)
#define FB_ADC_MAX              (4095U)

/** Position value indicating invalid / out-of-range feedback */
#define FB_POSITION_INVALID     (0xFFU)

/**
 * @brief Initialise feedback processor internal state and ADC peripheral.
 */
void feedback_processor_init(void);

/**
 * @brief Acquire a new ADC sample, validate, and map to logical position.
 *        Call periodically from the main loop.
 */
void feedback_processor_update(void);

/**
 * @brief Get the latest mapped flap position.
 * @param[out] p_position  Logical position (1–5) or FB_POSITION_INVALID.
 * @return 1 if the position is valid, 0 if invalid / out-of-range.
 */
uint8_t feedback_processor_get_position(uint8_t *p_position);

/**
 * @brief Get the raw ADC value from the last sample.
 * @return 12-bit ADC value (0–4095).
 */
uint16_t feedback_processor_get_raw_adc(void);

#endif /* FEEDBACK_PROCESSOR_H */
