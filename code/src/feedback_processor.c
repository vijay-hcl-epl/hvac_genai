/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation.
 *
 * Software Unit : Feedback Processor
 * Traces        : SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *                 SWE-REQ-028, SWE-REQ-030
 * Platform      : STM32F407G-DISC1, STM32 HAL ADC, 12-bit
 */

#include "feedback_processor.h"
#include "stm32f4xx_hal.h"

/* ---------- Platform binding ------------------------------------------- */
extern ADC_HandleTypeDef hadc1;  /* ADC1 – potentiometer channel */

/* ---------- Static position mapping table (SWE-REQ-027, SWE-REQ-030) --- */
/**
 * Each entry: { lowThreshold, highThreshold }
 * Zones divide the 12-bit ADC range (0..4095) into 5 equal bands.
 * SWE-REQ-028: No self-learning; table is fixed at compile time.
 */
typedef struct
{
    uint16_t low;
    uint16_t high;
} AdcZone_t;

static const AdcZone_t positionMap[FB_NUM_POSITIONS] =
{
    {    0U,   819U },   /* Position 0 – Fully closed  */
    {  820U,  1638U },   /* Position 1 – 25 %          */
    { 1639U,  2457U },   /* Position 2 – 50 %          */
    { 2458U,  3276U },   /* Position 3 – 75 %          */
    { 3277U,  4095U }    /* Position 4 – Fully open    */
};

/* ---------- Static data (SWE-REQ-036) ---------------------------------- */
static FeedbackData_t fbData;

/* ---------- Public API ------------------------------------------------- */

void FeedbackProcessor_Init(void)
{
    fbData.rawAdc   = 0U;
    fbData.position = 0U;
    fbData.valid    = 0U;
    fbData.state    = FB_STATE_INIT;
}

void FeedbackProcessor_Update(void)
{
    HAL_StatusTypeDef status;
    uint16_t adcValue;
    uint8_t  i;

    /* Start conversion and poll (blocking, single-channel) – SWE-REQ-017 */
    HAL_ADC_Start(&hadc1);
    status = HAL_ADC_PollForConversion(&hadc1, 10U);  /* 10 ms timeout */

    if (status == HAL_OK)
    {
        adcValue = (uint16_t)HAL_ADC_GetValue(&hadc1);

        /* Bounding / validation – SWE-REQ-011 */
        if (adcValue > FB_ADC_MAX)
        {
            fbData.valid = 0U;
            fbData.state = FB_STATE_INVALID;
        }
        else
        {
            fbData.rawAdc = adcValue;

            /* Table lookup – SWE-REQ-010, SWE-REQ-027 */
            fbData.valid = 0U;  /* assume invalid until matched */
            for (i = 0U; i < FB_NUM_POSITIONS; i++)
            {
                if ((adcValue >= positionMap[i].low) &&
                    (adcValue <= positionMap[i].high))
                {
                    fbData.position = i;
                    fbData.valid    = 1U;
                    fbData.state    = FB_STATE_READY;
                    break;
                }
            }
            if (fbData.valid == 0U)
            {
                fbData.state = FB_STATE_INVALID;
            }
        }
    }
    else
    {
        /* ADC conversion failed – mark invalid (SWE-REQ-031) */
        fbData.valid = 0U;
        fbData.state = FB_STATE_INVALID;
    }

    HAL_ADC_Stop(&hadc1);
}

uint8_t FeedbackProcessor_GetPosition(uint8_t *pPosition)
{
    if ((pPosition != ((void *)0)) && (fbData.valid == 1U))
    {
        *pPosition = fbData.position;
        return 1U;
    }
    return 0U;
}
