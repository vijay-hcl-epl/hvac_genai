/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation – ADC read, validate, map to position.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---- Hardware configuration (env-setup: ADC potentiometer feedback) ---- */

/** ADC handle – assumed configured externally by SystemInit (CubeMX) */
extern ADC_HandleTypeDef hadc1;

/* ---- Static position mapping table (SWE-REQ-027, SWE-REQ-028, SWE-REQ-030) ---- */

/**
 * @brief ADC centre-point for each logical position.
 *
 * 5 positions evenly distributed across 12-bit range (0..4095).
 * Position 0 ≈ 0, Position 4 ≈ 4095.
 * Traces: SWE-REQ-027, SWE-REQ-030
 */
static const uint16_t g_pos_adc_centre[FB_NUM_POSITIONS] =
{
    410U,   /* Position 0 */
    1230U,  /* Position 1 */
    2048U,  /* Position 2 */
    2867U,  /* Position 3 */
    3686U   /* Position 4 */
};

/**
 * @brief Half-width of each position band (SWE-REQ-030).
 *
 * A sample maps to position i if:
 *   |sample – centre[i]| <= half_band
 */
static const uint16_t g_pos_half_band = 400U;

/* ---- Internal static state (SWE-REQ-009, SWE-REQ-036) ---- */

static FeedbackData_t g_feedback;
static uint16_t       g_last_adc_raw;

/* ================================================================== */

void FeedbackProcessor_Init(void)
{
    g_feedback.position = 0U;
    g_feedback.valid    = 0U;
    g_last_adc_raw      = 0U;
}

/* ------------------------------------------------------------------ */

void FeedbackProcessor_Update(void)
{
    uint16_t adc_val;
    uint8_t  idx;
    uint8_t  mapped = 0U;

    /* Start ADC conversion and poll (SWE-REQ-017) */
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK)
    {
        adc_val = (uint16_t)HAL_ADC_GetValue(&hadc1);
    }
    else
    {
        /* ADC read failure – mark invalid (SWE-REQ-011) */
        g_feedback.valid = 0U;
        HAL_ADC_Stop(&hadc1);
        return;
    }
    HAL_ADC_Stop(&hadc1);

    /* Boundary validation (SWE-REQ-011) */
    if (adc_val > FB_ADC_MAX)
    {
        g_feedback.valid = 0U;
        return;
    }

    g_last_adc_raw = adc_val;

    /* Static table lookup – map ADC to position (SWE-REQ-027) */
    for (idx = 0U; idx < FB_NUM_POSITIONS; idx++)
    {
        uint16_t centre = g_pos_adc_centre[idx];
        uint16_t lo     = (centre > g_pos_half_band) ? (centre - g_pos_half_band) : 0U;
        uint16_t hi     = (uint16_t)(centre + g_pos_half_band);
        if (hi > FB_ADC_MAX)
        {
            hi = FB_ADC_MAX;
        }

        if ((adc_val >= lo) && (adc_val <= hi))
        {
            g_feedback.position = idx;
            g_feedback.valid    = 1U;
            mapped = 1U;
            break;
        }
    }

    if (mapped == 0U)
    {
        /* Out-of-range – no band matched (SWE-REQ-011, SWE-REQ-031) */
        g_feedback.valid = 0U;
    }
}

/* ------------------------------------------------------------------ */

FeedbackData_t FeedbackProcessor_GetPosition(void)
{
    return g_feedback;
}
