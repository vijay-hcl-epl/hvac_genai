/**
 * @file    feedback_processor.h
 * @brief   Feedback Processor software unit – header.
 *
 * Acquires ADC samples from the potentiometer, validates them,
 * and maps to a logical flap position using a fixed lookup table.
 *
 * Traceability:
 *   SWE-REQ-010  – Acquire ADC samples and interpret into logical positions.
 *   SWE-REQ-011  – Apply bounding/validation on ADC inputs.
 *   SWE-REQ-017  – Sample current flap position using logical ADC channel.
 *   SWE-REQ-027  – Fixed, static ADC-to-position mapping table.
 *   SWE-REQ-028  – No dynamic/self-learning configuration.
 *   SWE-REQ-030  – Store boundaries & mapping constants statically.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *   SWE-REQ-038  – All limits declared statically.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 */

#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

/* ---- Public Types --------------------------------------------------- */

/** @brief Feedback Processor states (LLD SM). */
typedef enum
{
    FB_STATE_INIT    = 0U,
    FB_STATE_READY,
    FB_STATE_INVALID
} FeedbackState_t;

/** @brief Feedback data – static allocation (SWE-REQ-009). */
typedef struct
{
    uint16_t        rawAdc;       /**< Latest raw ADC reading            */
    uint8_t         position;     /**< Mapped logical position 0..4     */
    bool            valid;        /**< True when mapping succeeded      */
    FeedbackState_t state;        /**< Current processor state          */
} FeedbackData_t;

/* ---- Public Constants ----------------------------------------------- */

/** @brief ADC resolution for STM32F407 (12-bit). */
#define FB_ADC_MAX_VALUE   (4095U)

/** @brief Number of position zones (must equal CMD_NUM_POSITIONS). */
#define FB_NUM_POSITIONS   (5U)

/**
 * @brief  ADC boundary thresholds for each position zone.
 *         Position i is valid when  ADC ∈ [lower[i], upper[i]].
 *         Statically initialised (SWE-REQ-030).
 */
extern const uint16_t FB_ADC_LOWER_BOUNDS[FB_NUM_POSITIONS];
extern const uint16_t FB_ADC_UPPER_BOUNDS[FB_NUM_POSITIONS];

/* ---- Public API ----------------------------------------------------- */

/**
 * @brief  Initialise feedback processor (state → INIT, clear data).
 *         [SWE-REQ-020]
 */
void FeedbackProcessor_Init(void);

/**
 * @brief  Trigger a new ADC acquisition, validate, and map.
 *         [SWE-REQ-010, SWE-REQ-011, SWE-REQ-017]
 */
void FeedbackProcessor_Update(void);

/**
 * @brief  Return the latest mapped position and validity.
 * @param[out] pPosition  Logical position 0..4.
 * @return true if the last reading was valid.
 *         [SWE-REQ-010]
 */
bool FeedbackProcessor_GetPosition(uint8_t *pPosition);

#endif /* FEEDBACK_PROCESSOR_H */
