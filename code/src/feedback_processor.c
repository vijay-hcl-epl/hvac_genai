/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1, STM32 HAL (ADC), bare-metal
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---------- Configuration constants (SWE-REQ-027, SWE-REQ-030, SWE-REQ-038) ---------- */

/** Number of logical positions */
#define FB_NUM_POSITIONS   (5U)

/**
 * ADC threshold boundaries for position mapping (12-bit ADC, 0-4095).
 * Position i is valid when: g_adc_lower[i] <= raw <= g_adc_upper[i]
 * Values assume linear potentiometer travel; configurable per hardware calibration.
 * (SWE-REQ-027, SWE-REQ-028 – static table, no self-learning)
 */
static const uint16_t g_adc_lower[FB_NUM_POSITIONS] =
{
    0U,     /* Position 0 – CLOSED */
    820U,   /* Position 1 – 25%   */
    1640U,  /* Position 2 – 50%   */
    2460U,  /* Position 3 – 75%   */
    3280U   /* Position 4 – OPEN  */
};

static const uint16_t g_adc_upper[FB_NUM_POSITIONS] =
{
    819U,   /* Position 0 */
    1639U,  /* Position 1 */
    2459U,  /* Position 2 */
    3279U,  /* Position 3 */
    4095U   /* Position 4 */
};

/* ---------- Static data (SWE-REQ-036, SWE-REQ-009) ---------- */

/** External ADC handle – defined in system_init.c */
extern ADC_HandleTypeDef hadc1;

static uint16_t g_raw_adc      = 0U;
static uint8_t  g_position     = 0U;
static uint8_t  g_valid        = FB_INVALID;

/* ---------- Public API ---------- */

void FeedbackProcessor_Init(void)
{
    g_raw_adc  = 0U;
    g_position = 0U;
    g_valid    = FB_INVALID;
}

void FeedbackProcessor_Update(void)
{
    uint32_t adc_value = 0U;
    uint8_t  i;
    uint8_t  mapped = 0U;

    /* Start ADC conversion and poll (SWE-REQ-017) */
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK)
    {
        adc_value = HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Stop(&hadc1);

    /* SWE-REQ-011: bounding / validation */
    if (adc_value > (uint32_t)FB_ADC_MAX)
    {
        g_valid = FB_INVALID;
        return;
    }

    g_raw_adc = (uint16_t)adc_value;

    /* SWE-REQ-010, SWE-REQ-027: static table lookup */
    mapped = 0U;
    for (i = 0U; i < FB_NUM_POSITIONS; i++)
    {
        if ((g_raw_adc >= g_adc_lower[i]) && (g_raw_adc <= g_adc_upper[i]))
        {
            g_position = i;
            mapped = 1U;
            break;
        }
    }

    if (mapped != 0U)
    {
        g_valid = FB_VALID;
    }
    else
    {
        g_valid = FB_INVALID;
    }
}

void FeedbackProcessor_GetPosition(uint8_t *p_position, uint8_t *p_valid)
{
    if ((p_position != (void *)0) && (p_valid != (void *)0))
    {
        *p_position = g_position;
        *p_valid    = g_valid;
    }
}
