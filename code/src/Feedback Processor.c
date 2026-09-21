#include "Feedback Processor.h"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;

typedef enum
{
    FEEDBACK_STATE_INIT = 0,
    FEEDBACK_STATE_READY,
    FEEDBACK_STATE_INVALID
} FeedbackProcessor_StateType;

typedef struct
{
    uint16_t min_adc;
    uint16_t max_adc;
    uint8_t position;
} FeedbackProcessor_MapEntryType;

static const FeedbackProcessor_MapEntryType feedback_map[4] =
{
    {0U,    1023U, 0U},
    {1024U, 2047U, 1U},
    {2048U, 3071U, 2U},
    {3072U, 4095U, 3U}
};

static uint16_t latest_adc;
static FeedbackProcessor_PositionType latest_position;
static FeedbackProcessor_StateType feedback_state;

static uint8_t FeedbackProcessor_MapAdc(uint16_t adc_value, uint8_t * position)
{
    uint8_t idx;
    uint8_t valid = 0U;

    for (idx = 0U; idx < 4U; idx++)
    {
        if ((adc_value >= feedback_map[idx].min_adc) && (adc_value <= feedback_map[idx].max_adc))
        {
            *position = feedback_map[idx].position;
            valid = 1U;
        }
    }

    return valid;
}

void FeedbackProcessor_Init(void)
{
    latest_adc = 0U;
    latest_position.position = 0U;
    latest_position.valid = 0U;
    feedback_state = FEEDBACK_STATE_INIT;
}

void FeedbackProcessor_Update(void)
{
    uint8_t mapped_position = 0U;

    if (HAL_ADC_Start(&hadc1) == HAL_OK)
    {
        if (HAL_ADC_PollForConversion(&hadc1, 1U) == HAL_OK)
        {
            latest_adc = (uint16_t)HAL_ADC_GetValue(&hadc1);
            if (FeedbackProcessor_MapAdc(latest_adc, &mapped_position) != 0U)
            {
                latest_position.position = mapped_position;
                latest_position.valid = 1U;
                feedback_state = FEEDBACK_STATE_READY;
            }
            else
            {
                latest_position.valid = 0U;
                feedback_state = FEEDBACK_STATE_INVALID;
            }
        }
        else
        {
            latest_position.valid = 0U;
            feedback_state = FEEDBACK_STATE_INVALID;
        }
        (void)HAL_ADC_Stop(&hadc1);
    }
    else
    {
        latest_position.valid = 0U;
        feedback_state = FEEDBACK_STATE_INVALID;
    }
}

FeedbackProcessor_PositionType FeedbackProcessor_GetPosition(void)
{
    return latest_position;
}

uint16_t FeedbackProcessor_GetAdcRaw(void)
{
    return latest_adc;
}
