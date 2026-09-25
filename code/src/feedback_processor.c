/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation – ADC acquisition, validation, position mapping.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030
 * Platform: STM32F407G-DISC1 / STM32 HAL / ADC1
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---- Static position mapping table [SWE-REQ-027, SWE-REQ-028, SWE-REQ-030] ---- */

/**
 * Position-to-ADC boundary table.
 * Each entry defines the upper ADC boundary for the corresponding position.
 * Position 1: ADC 0   – 819
 * Position 2: ADC 820 – 1638
 * Position 3: ADC 1639 – 2457
 * Position 4: ADC 2458 – 3276
 * Position 5: ADC 3277 – 4095
 *
 * Configurable responsiveness parameter [SWE-REQ-035]
 */
static const uint16_t position_adc_upper[CMD_NUM_POSITIONS_FB] =
{
    819U,
    1638U,
    2457U,
    3276U,
    4095U
};

/** Number of positions – kept in sync with command parser */
#define CMD_NUM_POSITIONS_FB    (5U)

/* ---- Internal state (static, no dynamic allocation) [SWE-REQ-036, SWE-REQ-038] ---- */
static uint16_t s_raw_adc;
static uint8_t  s_mapped_position;
static uint8_t  s_position_valid;

/* Extern ADC handle – expected from STM32CubeMX generated code */
extern ADC_HandleTypeDef hadc1;

/* ---- Private helpers ---- */

/**
 * @brief Map a validated ADC value to a logical position (1–5).
 * @param adc_val  12-bit ADC reading.
 * @return Mapped position (1–5).
 */
static uint8_t map_adc_to_position(uint16_t adc_val)
{
    uint8_t pos = 1U;
    uint8_t i;

    for (i = 0U; i < CMD_NUM_POSITIONS_FB; i++)
    {
        if (adc_val <= position_adc_upper[i])
        {
            pos = (uint8_t)(i + 1U);
            break;
        }
    }
    return pos;
}

/* ---- Public API ---- */

void feedback_processor_init(void)
{
    s_raw_adc         = 0U;
    s_mapped_position = FB_POSITION_INVALID;
    s_position_valid  = 0U;
}

void feedback_processor_update(void)
{
    /* Start ADC conversion, poll for result [SWE-REQ-017] */
    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK)
    {
        s_raw_adc = (uint16_t)HAL_ADC_GetValue(&hadc1);

        /* Bounding / validation [SWE-REQ-011] */
        if (s_raw_adc <= FB_ADC_MAX)
        {
            s_mapped_position = map_adc_to_position(s_raw_adc);
            s_position_valid  = 1U;
        }
        else
        {
            /* Out-of-range – mark invalid [SWE-REQ-031] */
            s_mapped_position = FB_POSITION_INVALID;
            s_position_valid  = 0U;
        }
    }
    else
    {
        /* ADC timeout / error – mark invalid */
        s_position_valid = 0U;
        s_mapped_position = FB_POSITION_INVALID;
    }

    HAL_ADC_Stop(&hadc1);
}

uint8_t feedback_processor_get_position(uint8_t *p_position)
{
    uint8_t valid = 0U;

    if (p_position != (void *)0)
    {
        *p_position = s_mapped_position;
        valid = s_position_valid;
    }
    return valid;
}

uint16_t feedback_processor_get_raw_adc(void)
{
    return s_raw_adc;
}
