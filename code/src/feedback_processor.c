/**
 * @file feedback_processor.c
 * @brief Feedback Processor implementation – ADC sampling, validation, position mapping.
 *
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *         SWE-REQ-028, SWE-REQ-030
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "feedback_processor.h"
#include "command_parser.h"   /* For position defines (CMD_POS_*) */
#include "stm32f4xx_hal.h"

/* ---- Private types ---------------------------------------------------- */

typedef enum
{
    FB_STATE_INIT    = 0U,
    FB_STATE_READY   = 1U,
    FB_STATE_INVALID = 2U
} FbState_t;

typedef struct
{
    FbState_t state;
    uint16_t  raw_adc;
    uint8_t   mapped_position;
    bool      valid;
} FbData_t;

/* ---- Private data ----------------------------------------------------- */

static FbData_t s_fb_data;

/* Extern ADC handle (defined in system_init.c). */
extern ADC_HandleTypeDef hadc1;

/**
 * Static position mapping table (SWE-REQ-027, SWE-REQ-028, SWE-REQ-030).
 * Each entry: { lower_bound, upper_bound, mapped_position }
 * Boundaries derived from potentiometer range divided into 5 equal zones.
 * ADC range considered valid: FB_ADC_LOW_BOUND .. FB_ADC_HIGH_BOUND
 *   Zone 1:   50 –  840  → FULLY_CLOSED (0x01)
 *   Zone 2:  841 – 1630  → QUARTER_OPEN (0x02)
 *   Zone 3: 1631 – 2420  → HALF_OPEN    (0x03)
 *   Zone 4: 2421 – 3210  → THREE_QTR    (0x04)
 *   Zone 5: 3211 – 4000  → FULLY_OPEN   (0x05)
 */
typedef struct
{
    uint16_t lower;
    uint16_t upper;
    uint8_t  position;
} AdcPosMapEntry_t;

static const AdcPosMapEntry_t s_adc_pos_map[CMD_NUM_POSITIONS] =
{
    { FB_ADC_LOW_BOUND,   840U,  CMD_POS_FULLY_CLOSED },
    { 841U,              1630U,  CMD_POS_QUARTER_OPEN },
    { 1631U,             2420U,  CMD_POS_HALF_OPEN    },
    { 2421U,             3210U,  CMD_POS_THREE_QTR    },
    { 3211U, FB_ADC_HIGH_BOUND,  CMD_POS_FULLY_OPEN   }
};

/* ---- Private helpers -------------------------------------------------- */

/**
 * @brief Map a validated ADC value to a logical position via table lookup.
 * @param adc_val  Validated ADC value.
 * @param p_pos    Pointer to store the resulting position.
 * @return true if mapping found, false otherwise.
 */
static bool Fb_MapAdcToPosition(uint16_t adc_val, uint8_t *p_pos)
{
    bool found = false;
    uint8_t idx;
    for (idx = 0U; idx < CMD_NUM_POSITIONS; idx++)
    {
        if ((adc_val >= s_adc_pos_map[idx].lower) &&
            (adc_val <= s_adc_pos_map[idx].upper))
        {
            *p_pos = s_adc_pos_map[idx].position;
            found  = true;
            break;
        }
    }
    return found;
}

/* ---- Public API ------------------------------------------------------- */

void FeedbackProcessor_Init(void)
{
    s_fb_data.state           = FB_STATE_INIT;
    s_fb_data.raw_adc         = 0U;
    s_fb_data.mapped_position = 0U;
    s_fb_data.valid           = false;
}

void FeedbackProcessor_Update(void)
{
    HAL_StatusTypeDef hal_status;
    uint16_t adc_val;
    uint8_t  pos = 0U;

    /* Start conversion and poll (SWE-REQ-017). */
    HAL_ADC_Start(&hadc1);
    hal_status = HAL_ADC_PollForConversion(&hadc1, 10U);

    if (hal_status == HAL_OK)
    {
        adc_val = (uint16_t)HAL_ADC_GetValue(&hadc1);
        s_fb_data.raw_adc = adc_val;

        /* Bound check (SWE-REQ-011). */
        if ((adc_val >= FB_ADC_LOW_BOUND) && (adc_val <= FB_ADC_HIGH_BOUND))
        {
            if (Fb_MapAdcToPosition(adc_val, &pos))
            {
                s_fb_data.mapped_position = pos;
                s_fb_data.valid           = true;
                s_fb_data.state           = FB_STATE_READY;
            }
            else
            {
                /* Mapping gap – treat as invalid. */
                s_fb_data.valid = false;
                s_fb_data.state = FB_STATE_INVALID;
            }
        }
        else
        {
            /* Out-of-range ADC – INVALID (SWE-REQ-031). */
            s_fb_data.valid = false;
            s_fb_data.state = FB_STATE_INVALID;
        }
    }
    else
    {
        /* ADC read failure – INVALID. */
        s_fb_data.valid = false;
        s_fb_data.state = FB_STATE_INVALID;
    }

    HAL_ADC_Stop(&hadc1);
}

void FeedbackProcessor_GetPosition(uint8_t *p_position, bool *p_valid)
{
    if ((p_position != (void *)0) && (p_valid != (void *)0))
    {
        *p_position = s_fb_data.mapped_position;
        *p_valid    = s_fb_data.valid;
    }
}

uint16_t FeedbackProcessor_GetRawADC(void)
{
    return s_fb_data.raw_adc;
}
