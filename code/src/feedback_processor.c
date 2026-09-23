/**
 * @file feedback_processor.c
 * @brief Feedback Processor Software Unit – Implementation
 *
 * Traceability:
 *   SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *   SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1, STM32 HAL (ADC1), bare-metal
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---------- Hardware binding (env-setup: ADC) ---------- */

/**
 * @brief ADC handle – ADC1 used for potentiometer feedback.
 *        Declared extern; created by peripheral-init in system_init.
 *        [SWE-REQ-017, SWE-REQ-019]
 */
extern ADC_HandleTypeDef hadc1;

/* ---------- Static configuration data ---------- */
/* Fixed, static mapping from ADC range to logical position.
 * [SWE-REQ-027, SWE-REQ-028, SWE-REQ-030]
 *
 * The 12-bit ADC range (0-4095) is divided into FEEDBACK_NUM_POSITIONS
 * equal bands.  The upper-boundary of each band is stored in this table.
 *
 * Position 1:    0  ..  819  (band width = 4096/5 ≈ 819)
 * Position 2:  820  .. 1638
 * Position 3: 1639  .. 2457
 * Position 4: 2458  .. 3276
 * Position 5: 3277  .. 4095
 *
 * [SWE-REQ-027, SWE-REQ-030, SWE-REQ-038]
 */
static const uint16_t s_posUpperBound[FEEDBACK_NUM_POSITIONS] =
{
    819U,   /* Position 1 upper bound */
    1638U,  /* Position 2 upper bound */
    2457U,  /* Position 3 upper bound */
    3276U,  /* Position 4 upper bound */
    4095U   /* Position 5 upper bound */
};

/**
 * @brief Minimum valid ADC value (lower bound).
 *        [SWE-REQ-011, SWE-REQ-030]
 */
#define FEEDBACK_ADC_MIN  (0U)

/* ---------- Static module data (no dynamic allocation) ---------- */
/* [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] */

/** Current state of the feedback processor state machine */
static FeedbackState_t s_state = FB_STATE_INIT;

/** Latest raw ADC sample */
static uint16_t s_adcRaw = 0U;

/** Latest mapped position result */
static FeedbackResult_t s_result = { 0U, false };

/* ---------- Private helpers ---------- */

/**
 * @brief Map a validated ADC value to a logical flap position.
 * @param adcVal  The bounded ADC value (0..4095).
 * @return Logical position 1..FEEDBACK_NUM_POSITIONS.
 *         [SWE-REQ-010, SWE-REQ-027]
 */
static uint8_t MapAdcToPosition(uint16_t adcVal)
{
    uint8_t pos;
    for (pos = 0U; pos < FEEDBACK_NUM_POSITIONS; pos++)
    {
        if (adcVal <= s_posUpperBound[pos])
        {
            return (pos + 1U);
        }
    }
    /* Should not reach here if bounds are correct; return last position */
    return FEEDBACK_NUM_POSITIONS;
}

/* ---------- Public API ---------- */

/**
 * @brief Initialise the Feedback Processor unit.
 *        [SWE-REQ-020]
 */
void FeedbackProcessor_Init(void)
{
    s_state          = FB_STATE_INIT;
    s_adcRaw         = 0U;
    s_result.position = 0U;
    s_result.valid    = false;
}

/**
 * @brief Acquire a new ADC sample, validate, and update mapped position.
 *
 * Uses HAL ADC polling to read a single conversion from ADC1.
 * Validates the sample against [FEEDBACK_ADC_MIN .. FEEDBACK_ADC_MAX].
 *
 * [SWE-REQ-010, SWE-REQ-011, SWE-REQ-017]
 */
void FeedbackProcessor_Update(void)
{
    HAL_StatusTypeDef adcStatus;

    /* Start ADC conversion [SWE-REQ-017] */
    adcStatus = HAL_ADC_Start(&hadc1);
    if (adcStatus != HAL_OK)
    {
        s_state        = FB_STATE_INVALID;
        s_result.valid = false;
        return;
    }

    /* Wait for conversion to complete (polling, short timeout) */
    adcStatus = HAL_ADC_PollForConversion(&hadc1, 10U);
    if (adcStatus != HAL_OK)
    {
        s_state        = FB_STATE_INVALID;
        s_result.valid = false;
        HAL_ADC_Stop(&hadc1);
        return;
    }

    /* Read raw ADC value */
    s_adcRaw = (uint16_t)HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    /* Bounding / validation [SWE-REQ-011] */
    if (s_adcRaw > FEEDBACK_ADC_MAX)
    {
        s_state        = FB_STATE_INVALID;
        s_result.valid = false;
        return;
    }

    /* Map to logical position [SWE-REQ-010, SWE-REQ-027] */
    s_result.position = MapAdcToPosition(s_adcRaw);
    s_result.valid    = true;
    s_state           = FB_STATE_READY;
}

/**
 * @brief Retrieve the latest mapped position and validity.
 *        [SWE-REQ-010, SWE-REQ-027]
 */
FeedbackResult_t FeedbackProcessor_GetPosition(void)
{
    return s_result;
}
