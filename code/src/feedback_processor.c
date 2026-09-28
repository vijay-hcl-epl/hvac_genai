/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation – ADC read, validate, map.
 *
 * Software Unit : Feedback Processor
 * Traceability  : SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *                 SWE-REQ-028, SWE-REQ-030
 *
 * Platform      : STM32F407G-DISC1, STM32 HAL
 *
 * CONFIGURATION GAP: The ADC handle (hadc1) and channel are assumed to be
 * initialised in system_init.c.  The specific ADC instance / channel must
 * be confirmed against the potentiometer wiring.
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ── External ADC handle (configured in system_init.c) ──────────────── */
extern ADC_HandleTypeDef hadc1;

/* ── Static position boundary table (SWE-REQ-027, SWE-REQ-030) ──────── */
typedef struct
{
    uint16_t low;
    uint16_t high;
} AdcBand_t;

static const AdcBand_t s_pos_table[FB_POSITION_COUNT] =
{
    { FB_POS0_LOW, FB_POS0_HIGH },
    { FB_POS1_LOW, FB_POS1_HIGH },
    { FB_POS2_LOW, FB_POS2_HIGH },
    { FB_POS3_LOW, FB_POS3_HIGH },
    { FB_POS4_LOW, FB_POS4_HIGH }
};

/* ── Module-scope static data (SWE-REQ-036, SWE-REQ-038) ───────────── */
static uint16_t       s_raw_adc   = 0U;
static uint8_t        s_position  = 0U;
static uint8_t        s_valid     = 0U;
static FbProc_State_t s_state     = FBPROC_STATE_INIT;

/* ── Private helpers ─────────────────────────────────────────────────── */

/**
 * @brief Read a single ADC conversion (blocking, short timeout).
 * @return Raw 12-bit ADC value, or 0xFFFF on error.
 */
static uint16_t ReadAdc(void)
{
    uint16_t value = 0xFFFFU;

    if (HAL_ADC_Start(&hadc1) == HAL_OK)
    {
        if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK)
        {
            value = (uint16_t)HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);
    }
    return value;
}

/**
 * @brief Map a raw ADC value to a logical position using the static table.
 * @param adc_val  Raw 12-bit ADC value.
 * @param[out] p_pos  Mapped position.
 * @return 1 if mapped successfully, 0 if out-of-bounds.
 */
static uint8_t MapAdcToPosition(uint16_t adc_val, uint8_t *p_pos)
{
    uint8_t i;
    uint8_t found = 0U;

    for (i = 0U; i < FB_POSITION_COUNT; i++)
    {
        if ((adc_val >= s_pos_table[i].low) && (adc_val <= s_pos_table[i].high))
        {
            *p_pos = i;
            found  = 1U;
            break;
        }
    }
    return found;
}

/* ── Public API ──────────────────────────────────────────────────────── */

void FbProc_Init(void)
{
    s_raw_adc  = 0U;
    s_position = 0U;
    s_valid    = 0U;
    s_state    = FBPROC_STATE_INIT;
}

void FbProc_Update(void)
{
    uint16_t adc_val;
    uint8_t  mapped_pos = 0U;

    adc_val = ReadAdc();

    /* SWE-REQ-011: bound/validate before use. */
    if (adc_val > FB_ADC_MAX)
    {
        /* Out-of-range or read error → INVALID */
        s_valid = 0U;
        s_state = FBPROC_STATE_INVALID;
    }
    else
    {
        s_raw_adc = adc_val;

        if (MapAdcToPosition(adc_val, &mapped_pos) != 0U)
        {
            s_position = mapped_pos;
            s_valid    = 1U;
            s_state    = FBPROC_STATE_READY;
        }
        else
        {
            /* Mapped outside defined bands → INVALID */
            s_valid = 0U;
            s_state = FBPROC_STATE_INVALID;
        }
    }
}

void FbProc_GetPosition(FbProc_Result_t *p_result)
{
    if (p_result != (void *)0)
    {
        p_result->position = s_position;
        p_result->valid    = s_valid;
        p_result->raw_adc  = s_raw_adc;
        p_result->state    = s_state;
    }
}
