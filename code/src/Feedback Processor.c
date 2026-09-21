#include "Feedback Processor.h"

/* ADC potentiometer feedback processing using a fixed static mapping table.
 * Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030, SWE-REQ-031.
 */

extern ADC_HandleTypeDef hadc1;

typedef struct
{
    uint16_t min_adc;
    uint16_t max_adc;
    Hvac_FlapPosition_t position;
} FeedbackProcessor_MapEntry_t;

static const FeedbackProcessor_MapEntry_t FeedbackProcessor_PositionMap[] =
{
    { 0U,    1023U, HVAC_FLAP_POSITION_FACE },
    { 1024U, 2047U, HVAC_FLAP_POSITION_BI_LEVEL },
    { 2048U, 3071U, HVAC_FLAP_POSITION_FOOT },
    { 3072U, 4095U, HVAC_FLAP_POSITION_DEFROST }
};

static FeedbackProcessor_State_t FeedbackProcessor_State = FEEDBACK_PROCESSOR_STATE_INIT;
static FeedbackProcessor_Position_t FeedbackProcessor_LatestPosition =
{
    false,
    HVAC_FLAP_POSITION_INVALID,
    0U
};

static bool FeedbackProcessor_MapAdc(uint16_t adc_sample, Hvac_FlapPosition_t * position)
{
    bool valid = false;
    uint32_t index;

    if (position != (Hvac_FlapPosition_t *)0)
    {
        for (index = 0U; index < (sizeof(FeedbackProcessor_PositionMap) / sizeof(FeedbackProcessor_PositionMap[0])); index++)
        {
            if ((adc_sample >= FeedbackProcessor_PositionMap[index].min_adc) &&
                (adc_sample <= FeedbackProcessor_PositionMap[index].max_adc))
            {
                *position = FeedbackProcessor_PositionMap[index].position;
                valid = true;
                break;
            }
        }
    }

    return valid;
}

void FeedbackProcessor_Init(void)
{
    FeedbackProcessor_State = FEEDBACK_PROCESSOR_STATE_INIT;
    FeedbackProcessor_LatestPosition.valid = false;
    FeedbackProcessor_LatestPosition.position = HVAC_FLAP_POSITION_INVALID;
    FeedbackProcessor_LatestPosition.adc_sample = 0U;
}

void FeedbackProcessor_Update(void)
{
    uint32_t adc_value;
    Hvac_FlapPosition_t mapped_position = HVAC_FLAP_POSITION_INVALID;
    HAL_StatusTypeDef hal_status;

    hal_status = HAL_ADC_Start(&hadc1);
    if (hal_status == HAL_OK)
    {
        hal_status = HAL_ADC_PollForConversion(&hadc1, 1U);
        if (hal_status == HAL_OK)
        {
            adc_value = HAL_ADC_GetValue(&hadc1);
            (void)HAL_ADC_Stop(&hadc1);

            if ((adc_value <= 4095U) && (FeedbackProcessor_MapAdc((uint16_t)adc_value, &mapped_position) == true))
            {
                FeedbackProcessor_LatestPosition.valid = true;
                FeedbackProcessor_LatestPosition.position = mapped_position;
                FeedbackProcessor_LatestPosition.adc_sample = (uint16_t)adc_value;
                FeedbackProcessor_State = FEEDBACK_PROCESSOR_STATE_READY;
            }
            else
            {
                FeedbackProcessor_LatestPosition.valid = false;
                FeedbackProcessor_LatestPosition.position = HVAC_FLAP_POSITION_INVALID;
                FeedbackProcessor_State = FEEDBACK_PROCESSOR_STATE_INVALID;
            }
        }
        else
        {
            (void)HAL_ADC_Stop(&hadc1);
            FeedbackProcessor_LatestPosition.valid = false;
            FeedbackProcessor_LatestPosition.position = HVAC_FLAP_POSITION_INVALID;
            FeedbackProcessor_State = FEEDBACK_PROCESSOR_STATE_INVALID;
        }
    }
    else
    {
        FeedbackProcessor_LatestPosition.valid = false;
        FeedbackProcessor_LatestPosition.position = HVAC_FLAP_POSITION_INVALID;
        FeedbackProcessor_State = FEEDBACK_PROCESSOR_STATE_INVALID;
    }
}

FeedbackProcessor_Position_t FeedbackProcessor_GetPosition(void)
{
    return FeedbackProcessor_LatestPosition;
}

FeedbackProcessor_State_t FeedbackProcessor_GetState(void)
{
    return FeedbackProcessor_State;
}
