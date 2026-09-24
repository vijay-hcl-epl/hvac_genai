/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---- Platform: ADC handle (configured for potentiometer channel) ---- */
extern ADC_HandleTypeDef hadc1;

/* ---- Static position-mapping table [SWE-REQ-027, SWE-REQ-028, SWE-REQ-030] ----
 *
 * Maps ADC range to logical flap positions 1..5.
 * Each entry defines the upper-bound (inclusive) of the ADC range for that position.
 * Boundaries are configurable at compile-time; no self-learning [SWE-REQ-028].
 *
 * Example 12-bit ADC (0-4095) split into 5 equal zones:
 *   Position 1:    0 –  819
 *   Position 2:  820 – 1638
 *   Position 3: 1639 – 2457
 *   Position 4: 2458 – 3276
 *   Position 5: 3277 – 4095
 */
static const uint16_t posUpperBound[FB_NUM_POSITIONS] =
{
    819U,   /* Position 1 upper bound */
    1638U,  /* Position 2 upper bound */
    2457U,  /* Position 3 upper bound */
    3276U,  /* Position 4 upper bound */
    4095U   /* Position 5 upper bound */
};

/** Lower boundary for valid ADC reading */
#define FB_ADC_MIN_VALID  (0U)

/** Upper boundary for valid ADC reading */
#define FB_ADC_MAX_VALID  (FB_ADC_MAX_VALUE)

/* ---- Module static data [SWE-REQ-036, SWE-REQ-038] ---- */
static FbResult_t s_fbResult;

/* ---- Private helpers ---- */

/**
 * @brief Map a validated raw ADC value to a logical position (1..5).
 * @param adcVal  Raw ADC value (assumed already validated in-range)
 * @return Logical position 1..5
 */
static uint8_t Fb_MapPosition(uint16_t adcVal)
{
    uint8_t pos;

    for (pos = 0U; pos < FB_NUM_POSITIONS; pos++)
    {
        if (adcVal <= posUpperBound[pos])
        {
            break;
        }
    }
    /* pos is 0-indexed; logical positions are 1-based */
    return (pos + 1U);
}

/* ---- Public API ---- */

void FeedbackProcessor_Init(void)
{
    s_fbResult.position = 0U;
    s_fbResult.valid    = FB_INVALID;
    s_fbResult.rawAdc   = 0U;
    s_fbResult.state    = FB_STATE_INIT;
}

void FeedbackProcessor_Update(void)
{
    HAL_StatusTypeDef adcStatus;
    uint16_t adcVal;

    /* Start ADC conversion [SWE-REQ-017] */
    adcStatus = HAL_ADC_Start(&hadc1);

    if (adcStatus == HAL_OK)
    {
        /* Wait for conversion (blocking, single-shot) */
        adcStatus = HAL_ADC_PollForConversion(&hadc1, 10U);
    }

    if (adcStatus == HAL_OK)
    {
        adcVal = (uint16_t)HAL_ADC_GetValue(&hadc1);

        /* Bounding / validation [SWE-REQ-011] */
        if (adcVal <= FB_ADC_MAX_VALID)
        {
            s_fbResult.rawAdc   = adcVal;
            s_fbResult.position = Fb_MapPosition(adcVal);
            s_fbResult.valid    = FB_VALID;
            s_fbResult.state    = FB_STATE_READY;
        }
        else
        {
            /* Out-of-range → invalid [SWE-REQ-031] */
            s_fbResult.valid = FB_INVALID;
            s_fbResult.state = FB_STATE_INVALID;
        }
    }
    else
    {
        /* ADC error → invalid */
        s_fbResult.valid = FB_INVALID;
        s_fbResult.state = FB_STATE_INVALID;
    }

    HAL_ADC_Stop(&hadc1);
}

FbResult_t FeedbackProcessor_GetPosition(void)
{
    return s_fbResult;
}
