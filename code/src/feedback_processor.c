/**
 * @file    feedback_processor.c
 * @brief   Feedback Processor software unit – implementation.
 *
 * Traceability:
 *   SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028,
 *   SWE-REQ-030, SWE-REQ-036, SWE-REQ-038.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 *          ADC Channel connected to potentiometer feedback.
 */

/* ---- Includes ------------------------------------------------------- */
#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---- Extern HAL Handle ---------------------------------------------- */
extern ADC_HandleTypeDef hadc1;

/* ---- Static Lookup Tables (SWE-REQ-027, SWE-REQ-030) --------------- */

/**
 * @brief  Lower ADC boundaries for each position zone (12-bit ADC, 0-4095).
 *         Zone i valid when rawAdc >= FB_ADC_LOWER_BOUNDS[i]
 *                        AND rawAdc <= FB_ADC_UPPER_BOUNDS[i].
 *         Values assume linear potentiometer travel across 5 zones.
 *         Statically initialised, configurable (SWE-REQ-030, SWE-REQ-038).
 */
const uint16_t FB_ADC_LOWER_BOUNDS[FB_NUM_POSITIONS] =
{
       0U,   /* Position 0 – CLOSED      */
     820U,   /* Position 1 – 25 %        */
    1640U,   /* Position 2 – 50 %        */
    2460U,   /* Position 3 – 75 %        */
    3280U    /* Position 4 – FULLY OPEN  */
};

const uint16_t FB_ADC_UPPER_BOUNDS[FB_NUM_POSITIONS] =
{
     819U,   /* Position 0 */
    1639U,   /* Position 1 */
    2459U,   /* Position 2 */
    3279U,   /* Position 3 */
    4095U    /* Position 4 */
};

/* ---- Static Data (SWE-REQ-009, SWE-REQ-036) ------------------------ */

static FeedbackData_t s_fbData;

/* ---- Private Helpers ------------------------------------------------ */

/**
 * @brief  Read raw ADC value from the potentiometer channel.
 * @return 12-bit ADC sample (0..4095).
 *         [SWE-REQ-017]
 */
static uint16_t FB_ReadAdc(void)
{
    uint16_t adcValue = 0U;

    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK)
    {
        adcValue = (uint16_t)HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Stop(&hadc1);

    return adcValue;
}

/**
 * @brief  Map a validated ADC value to a logical position via table lookup.
 * @param  adcVal  Bounded ADC value.
 * @param[out] pPos  Mapped position.
 * @return true if mapping succeeded.
 *         [SWE-REQ-010, SWE-REQ-027, SWE-REQ-028]
 */
static bool FB_MapToPosition(uint16_t adcVal, uint8_t *pPos)
{
    uint8_t i;
    for (i = 0U; i < FB_NUM_POSITIONS; i++)
    {
        if ((adcVal >= FB_ADC_LOWER_BOUNDS[i]) &&
            (adcVal <= FB_ADC_UPPER_BOUNDS[i]))
        {
            *pPos = i;
            return true;
        }
    }
    return false;
}

/* ---- Public API Implementation -------------------------------------- */

/* [SWE-REQ-020] */
void FeedbackProcessor_Init(void)
{
    s_fbData.rawAdc   = 0U;
    s_fbData.position = 0U;
    s_fbData.valid    = false;
    s_fbData.state    = FB_STATE_INIT;
}

/* [SWE-REQ-010, SWE-REQ-011, SWE-REQ-017] */
void FeedbackProcessor_Update(void)
{
    uint16_t raw;
    uint8_t  pos = 0U;

    raw = FB_ReadAdc();
    s_fbData.rawAdc = raw;

    /* Bounding / validation (SWE-REQ-011). */
    if (raw > FB_ADC_MAX_VALUE)
    {
        s_fbData.valid = false;
        s_fbData.state = FB_STATE_INVALID;
        return;
    }

    /* Table lookup mapping (SWE-REQ-010, SWE-REQ-027). */
    if (FB_MapToPosition(raw, &pos))
    {
        s_fbData.position = pos;
        s_fbData.valid    = true;
        s_fbData.state    = FB_STATE_READY;
    }
    else
    {
        /* ADC in dead-zone / out of any defined range. */
        s_fbData.valid = false;
        s_fbData.state = FB_STATE_INVALID;
    }
}

/* [SWE-REQ-010] */
bool FeedbackProcessor_GetPosition(uint8_t *pPosition)
{
    if ((pPosition != (void *)0) && (s_fbData.valid == true))
    {
        *pPosition = s_fbData.position;
        return true;
    }
    return false;
}
