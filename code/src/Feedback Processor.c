#include "Feedback Processor.h"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;

#define ADC_MAX_VALUE                 (4095U)
#define ADC_VALID                     (1U)
#define ADC_INVALID                   (0U)
#define POSITION_TABLE_SIZE           (4U)

typedef struct
{
    uint16_t minimum;
    uint16_t maximum;
    uint8_t position;
} Feedback_Position_Map_t;

typedef struct
{
    uint16_t latest_adc;
    uint8_t mapped_position;
    uint8_t valid;
} Feedback_State_t;

static Feedback_State_t feedback_state;
static const Feedback_Position_Map_t feedback_map[POSITION_TABLE_SIZE] =
{
    { 0U,    1023U, 0U },
    { 1024U, 2047U, 1U },
    { 2048U, 3071U, 2U },
    { 3072U, 4095U, 3U }
};

void Feedback_Processor_Init(void)
{
    feedback_state.latest_adc = 0U;
    feedback_state.mapped_position = 0U;
    feedback_state.valid = ADC_INVALID;
}

void Feedback_Processor_Update(void)
{
    uint32_t adc_value = 0U;
    uint8_t index = 0U;
    uint8_t mapped = ADC_INVALID;

    if (HAL_ADC_Start(&hadc1) == HAL_OK)
    {
        if (HAL_ADC_PollForConversion(&hadc1, 0U) == HAL_OK)
        {
            adc_value = HAL_ADC_GetValue(&hadc1);
            if (adc_value <= ADC_MAX_VALUE)
            {
                feedback_state.latest_adc = (uint16_t)adc_value;
                for (index = 0U; index < POSITION_TABLE_SIZE; index++)
                {
                    if ((feedback_state.latest_adc >= feedback_map[index].minimum) &&
                        (feedback_state.latest_adc <= feedback_map[index].maximum))
                    {
                        feedback_state.mapped_position = feedback_map[index].position;
                        feedback_state.valid = ADC_VALID;
                        mapped = ADC_VALID;
                        break;
                    }
                }
            }
        }
        (void)HAL_ADC_Stop(&hadc1);
    }

    if (mapped == ADC_INVALID)
    {
        feedback_state.valid = ADC_INVALID;
    }
}

void Feedback_Processor_Get_Position(uint8_t * position, uint8_t * valid)
{
    if ((position != (void *)0) && (valid != (void *)0))
    {
        *position = feedback_state.mapped_position;
        *valid = feedback_state.valid;
    }
}

uint16_t Feedback_Processor_Get_Last_Adc(void)
{
    return feedback_state.latest_adc;
}
