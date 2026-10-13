/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation, and position mapping.
 *
 * Software Unit: Feedback Processor
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (12-bit ADC)
 *
 * ASSUMPTIONS (not verified on hardware – calibration required):
 *   - ADC channel and GPIO pin are configured by system_init via CubeMX/HAL.
 *   - The potentiometer ADC range 0..4095 is divided into 5 equal zones
 *     mapping to positions 1..5.  Boundary thresholds are placeholders and
 *     MUST be calibrated for the actual mechanical linkage.
 *   - ADC values outside ADC_RAW_MIN..ADC_RAW_MAX are treated as invalid.
 */
#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

/** 12-bit ADC boundaries (STM32F407 ADC). */
#define FB_ADC_RAW_MIN   0U
#define FB_ADC_RAW_MAX   4095U

/** Number of discrete flap positions mapped from ADC range. */
#define FB_NUM_POSITIONS 5U

/** Feedback processor states per LLD §Feedback Processor. */
typedef enum
{
    FB_STATE_INIT    = 0U,
    FB_STATE_READY   = 1U,
    FB_STATE_INVALID = 2U
} fb_state_t;

/**
 * @brief Initialise the Feedback Processor (clear state, set INIT).
 * Traces: SWE-REQ-020
 */
void feedback_processor_init(void);

/**
 * @brief Acquire a new ADC sample, validate, and map to a logical position.
 *
 * Reads the ADC channel via HAL, applies bounding, and performs a static
 * table lookup to determine the current flap position.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027
 */
void feedback_processor_update(void);

/**
 * @brief Get the latest mapped position and validity.
 *
 * Traces: SWE-REQ-010, SWE-REQ-027, SWE-REQ-030
 *
 * @param[out] position  Pointer to store the mapped position (1..FB_NUM_POSITIONS).
 * @param[out] valid     Pointer to store validity flag.
 */
void feedback_processor_get_position(uint8_t *position, bool *valid);

/**
 * @brief Return the current processor state.
 */
fb_state_t feedback_processor_get_state(void);

#endif /* FEEDBACK_PROCESSOR_H */
