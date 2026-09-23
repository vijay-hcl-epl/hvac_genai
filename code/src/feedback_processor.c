/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation – ADC sampling, validation, position mapping.
 *
 * Software Unit: Feedback Processor
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (ADC1, 12-bit)
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---------- Static (file-scope) data [SWE-REQ-009, SWE-REQ-036] ---------- */

/** Feedback Processor internal state */
static FeedbackProcessorState_t s_State = FBPROC_STATE_INIT;

/** Latest raw ADC value */
static uint16_t s_LatestAdcValue = 0U;

/** Latest mapped position result */
static FeedbackResult_t s_CurrentPosition = { 0U, false };

/**
 * @brief Static position mapping table (ADC upper-bound per position).
 *        Position 1: ADC 100..860
 *        Position 2: ADC 861..1620
 *        Position 3: ADC 1621..2380
 *        Position 4: ADC 2381..3140
 *        Position 5: ADC 3141..3900
 *
 * Fixed mapping, no self-learning [SWE-REQ-027, SWE-REQ-028].
 * Stored as statically initialised const [SWE-REQ-030, SWE-REQ-038].
 */
static const uint16_t s_PositionUpperBound[FEEDBACK_NUM_POSITIONS] =
{
    860U,   /* Position 1 upper bound */
    1620U,  /* Position 2 upper bound */
    2380U,  /* Position 3 upper bound */
    3140U,  /* Position 4 upper bound */
    3900U   /* Position 5 upper bound */
};

/* External ADC handle (defined in system_init.c / STM32CubeMX generated) */
extern ADC_HandleTypeDef hadc1;

/* ---------- Internal helpers -------------------------------------------- */

/**
 * @brief Map a validated ADC value to a logical position (1..5).
 * @param adc_val  The bounded ADC value.
 * @return Logical position 1..5, or 0 if mapping fails.
 *         [SWE-REQ-010, SWE-REQ-027]
 */
static uint8_t FeedbackProcessor_MapToPosition(uint16_t adc_val)
{
    uint8_t pos = 0U;
    uint8_t idx;

    for (idx = 0U; idx < FEEDBACK_NUM_POSITIONS; idx++)
    {
        if (adc_val <= s_PositionUpperBound[idx])
        {
            pos = idx + 1U;
            break;
        }
    }
    return pos;
}

/* ---------- Public API -------------------------------------------------- */

void FeedbackProcessor_Init(void)
{
    s_State                  = FBPROC_STATE_INIT;
    s_LatestAdcValue         = 0U;
    s_CurrentPosition.position = 0U;
    s_CurrentPosition.valid    = false;
}

void FeedbackProcessor_Update(void)
{
    HAL_StatusTypeDef hal_status;
    uint16_t adc_raw = 0U;
    uint8_t  mapped_pos;

    /* Start ADC conversion and poll [SWE-REQ-017] */
    hal_status = HAL_ADC_Start(&hadc1);
    if (hal_status == HAL_OK)
    {
        hal_status = HAL_ADC_PollForConversion(&hadc1, 10U);
    }

    if (hal_status == HAL_OK)
    {
        adc_raw = (uint16_t)HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);

        s_LatestAdcValue = adc_raw;

        /* Boundary / validation check [SWE-REQ-011] */
        if ((adc_raw >= FEEDBACK_ADC_MIN) && (adc_raw <= FEEDBACK_ADC_MAX))
        {
            mapped_pos = FeedbackProcessor_MapToPosition(adc_raw);

            if (mapped_pos != 0U)
            {
                s_CurrentPosition.position = mapped_pos;
                s_CurrentPosition.valid    = true;
                s_State                    = FBPROC_STATE_READY;
            }
            else
            {
                /* Mapping failure – treat as invalid */
                s_CurrentPosition.valid = false;
                s_State                 = FBPROC_STATE_INVALID;
            }
        }
        else
        {
            /* Out-of-range ADC value – INVALID [SWE-REQ-011, SWE-REQ-031] */
            s_CurrentPosition.valid = false;
            s_State                 = FBPROC_STATE_INVALID;
        }
    }
    else
    {
        /* ADC acquisition failure */
        s_CurrentPosition.valid = false;
        s_State                 = FBPROC_STATE_INVALID;
        HAL_ADC_Stop(&hadc1);
    }
}

FeedbackResult_t FeedbackProcessor_GetPosition(void)
{
    return s_CurrentPosition;
}
