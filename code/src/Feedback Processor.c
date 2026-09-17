#include "Feedback Processor.h"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;

#define FEEDBACK_PROCESSOR_MAP_COUNT (4U)
#define FEEDBACK_PROCESSOR_ADC_MAX   (4095U)

typedef enum
{
    FEEDBACK_PROCESSOR_STATE_INIT = 0,
    FEEDBACK_PROCESSOR_STATE_READY,
    FEEDBACK_PROCESSOR_STATE_INVALID
} Feedback_Processor_StateType;

typedef struct
{
    uint16_t low;
    uint16_t high;
    uint8_t position;
} Feedback_Processor_MapType;

static const Feedback_Processor_MapType Feedback_Processor_PositionMap[FEEDBACK_PROCESSOR_MAP_COUNT] =
{
    { 0U,    1023U, 0U },
    { 1024U, 2047U, 1U },
    { 2048U, 3071U, 2U },
    { 3072U, 4095U, 3U }
};

static Feedback_Processor_StateType Feedback_Processor_State = FEEDBACK_PROCESSOR_STATE_INIT;
static uint16_t Feedback_Processor_LatestAdc = 0U;
static uint8_t Feedback_Processor_Position = 0U;
static bool Feedback_Processor_Valid = false;

void Feedback_Processor_Init(void)
{
    Feedback_Processor_State = FEEDBACK_PROCESSOR_STATE_INIT;
    Feedback_Processor_LatestAdc = 0U;
    Feedback_Processor_Position = 0U;
    Feedback_Processor_Valid = false;
}

void Feedback_Processor_Update(void)
{
    uint32_t adc_raw = 0UL;
    uint8_t index = 0U;
    bool mapped = false;

    if (HAL_ADC_Start(&hadc1) == HAL_OK)
    {
        if (HAL_ADC_PollForConversion(&hadc1, 0U) == HAL_OK)
        {
            adc_raw = HAL_ADC_GetValue(&hadc1);
            if (adc_raw <= (uint32_t)FEEDBACK_PROCESSOR_ADC_MAX)
            {
                Feedback_Processor_LatestAdc = (uint16_t)adc_raw;

                for (index = 0U; index < FEEDBACK_PROCESSOR_MAP_COUNT; index++)
                {
                    if ((Feedback_Processor_LatestAdc >= Feedback_Processor_PositionMap[index].low) &&
                        (Feedback_Processor_LatestAdc <= Feedback_Processor_PositionMap[index].high))
                    {
                        Feedback_Processor_Position = Feedback_Processor_PositionMap[index].position;
                        Feedback_Processor_Valid = true;
                        Feedback_Processor_State = FEEDBACK_PROCESSOR_STATE_READY;
                        mapped = true;
                        break;
                    }
                }
            }
        }
        (void)HAL_ADC_Stop(&hadc1);
    }

    if (mapped == false)
    {
        Feedback_Processor_Valid = false;
        Feedback_Processor_State = FEEDBACK_PROCESSOR_STATE_INVALID;
    }
}

bool Feedback_Processor_GetPosition(uint8_t * position)
{
    bool ret = false;

    if ((position != (void *)0) && (Feedback_Processor_Valid == true))
    {
        *position = Feedback_Processor_Position;
        ret = true;
    }

    return ret;
}

uint16_t Feedback_Processor_GetLatestAdc(void)
{
    return Feedback_Processor_LatestAdc;
}
