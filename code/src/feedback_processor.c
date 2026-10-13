/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation.
 *
 * Software Unit: Feedback Processor
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (ADC1)
 * No dynamic allocation (SWE-REQ-036).  All state is static.
 *
 * ASSUMPTIONS / CALIBRATION NOTE:
 *   - ADC1 Channel 1 (PA1) is assumed for the potentiometer.
 *   - The 12-bit ADC range (0..4095) is divided into 5 equal zones.
 *     Threshold boundaries are PLACEHOLDERS and MUST be calibrated on
 *     the actual mechanical assembly before deployment.
 *   - hadc1 is declared extern; it is initialised in system_init.c.
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---- Extern HAL handle (initialised in system_init.c) ---- */
extern ADC_HandleTypeDef hadc1;

/* ---- Static position boundary table [SWE-REQ-027, SWE-REQ-030] ---- */

/**
 * Upper ADC thresholds for each position zone (0-indexed).
 * Position 1 : ADC   0 ..  819
 * Position 2 : ADC 820 .. 1638
 * Position 3 : ADC 1639 .. 2457
 * Position 4 : ADC 2458 .. 3276
 * Position 5 : ADC 3277 .. 4095
 *
 * WARNING: These values are evenly spaced design placeholders.
 *          Calibrate for the actual potentiometer / gear linkage.
 */
static const uint16_t s_pos_upper_threshold[FB_NUM_POSITIONS] =
{
     819U,   /* Position 1 upper bound */
    1638U,   /* Position 2 upper bound */
    2457U,   /* Position 3 upper bound */
    3276U,   /* Position 4 upper bound */
    4095U    /* Position 5 upper bound */
};

/* ---- Module static state [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] ---- */

static uint16_t   s_raw_adc   = 0U;
static uint8_t    s_position  = 0U;
static bool       s_valid     = false;
static fb_state_t s_state     = FB_STATE_INIT;

/* ---- Private helpers ---- */

/**
 * @brief Map a validated ADC value to a logical position (1..FB_NUM_POSITIONS).
 * @param adc_val  Bounded ADC value (0..4095).
 * @return Position 1..5, or 0 on mapping error.
 */
static uint8_t map_adc_to_position(uint16_t adc_val)
{
    uint8_t i;
    for (i = 0U; i < FB_NUM_POSITIONS; i++)
    {
        if (adc_val <= s_pos_upper_threshold[i])
        {
            return (i + 1U);
        }
    }
    return 0U;  /* should not reach if thresholds cover full range */
}

/* ---- Public API ---- */

void feedback_processor_init(void)
{
    s_raw_adc  = 0U;
    s_position = 0U;
    s_valid    = false;
    s_state    = FB_STATE_INIT;
}

/*
 * SWE-REQ-010 : acquire ADC, interpret to logical position
 * SWE-REQ-011 : bound / validate ADC before use
 * SWE-REQ-017 : sample via ADC channel
 * SWE-REQ-027 : fixed static mapping
 * SWE-REQ-028 : no self-learning
 */
void feedback_processor_update(void)
{
    HAL_StatusTypeDef hal_status;
    uint32_t adc_raw_32;

    /* Start a single-conversion poll [SWE-REQ-017] */
    hal_status = HAL_ADC_Start(&hadc1);
    if (hal_status != HAL_OK)
    {
        s_valid = false;
        s_state = FB_STATE_INVALID;
        return;
    }

    hal_status = HAL_ADC_PollForConversion(&hadc1, 10U);  /* 10 ms timeout */
    if (hal_status != HAL_OK)
    {
        s_valid = false;
        s_state = FB_STATE_INVALID;
        HAL_ADC_Stop(&hadc1);
        return;
    }

    adc_raw_32 = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    /* Bounding / validation [SWE-REQ-011] */
    if (adc_raw_32 > (uint32_t)FB_ADC_RAW_MAX)
    {
        s_valid = false;
        s_state = FB_STATE_INVALID;
        return;
    }

    s_raw_adc = (uint16_t)adc_raw_32;

    /* Map to position [SWE-REQ-010, SWE-REQ-027] */
    uint8_t pos = map_adc_to_position(s_raw_adc);
    if ((pos == 0U) || (pos > FB_NUM_POSITIONS))
    {
        s_valid = false;
        s_state = FB_STATE_INVALID;
        return;
    }

    s_position = pos;
    s_valid    = true;
    s_state    = FB_STATE_READY;
}

void feedback_processor_get_position(uint8_t *position, bool *valid)
{
    if (position != ((void *)0))
    {
        *position = s_position;
    }
    if (valid != ((void *)0))
    {
        *valid = s_valid;
    }
}

fb_state_t feedback_processor_get_state(void)
{
    return s_state;
}
