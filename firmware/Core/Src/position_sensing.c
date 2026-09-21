#include "position_sensing.h"
#include "stm32f4xx_hal.h"

#ifndef FLAP_POSITION_INVALID
#define FLAP_POSITION_INVALID 0xFFU
#endif

#define ADC_POLL_TIMEOUT 2U

extern ADC_HandleTypeDef hadc1;

typedef struct
{
    uint16_t min;
    uint16_t max;
} PositionStopRange_t;

static const PositionStopRange_t s_stop_ranges[6] =
{
    {4055U, 4065U},
    {3837U, 3857U},
    {3563U, 3593U},
    {3309U, 3329U},
    {2022U, 2042U},
    { 315U,  335U}
};

/* Internal state */
static uint16_t s_adc_value = 0U;
static uint8_t s_logical_position = FLAP_POSITION_INVALID;
static uint8_t s_position_valid = 0U;

void PositionSensing_Init(void)
{
    /* SWE-REQ-040: Initialize ADC state */
    s_adc_value = 0U;
    s_logical_position = FLAP_POSITION_INVALID;
    s_position_valid = 0U;
}

static uint8_t Position_GetFromADC(uint16_t adc)
{
    if (adc > 4000U) { return 0U; }
    if (adc > 3750U) { return 1U; }
    if (adc > 3480U) { return 2U; }
    if (adc > 2500U) { return 3U; }
    if (adc > 1000U) { return 4U; }
    return 5U;
}

uint8_t PositionSensing_IsAtTarget(uint8_t target)
{
    if (target >= 6U)
    {
        return 0U;
    }

    if ((s_adc_value >= s_stop_ranges[target].min) &&
        (s_adc_value <= s_stop_ranges[target].max))
    {
        return 1U;
    }

    return 0U;
}

void PositionSensing_Update(void)
{
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, ADC_POLL_TIMEOUT) == HAL_OK)
    {
        s_adc_value = (uint16_t)HAL_ADC_GetValue(&hadc1);

        s_logical_position = Position_GetFromADC(s_adc_value);
        s_position_valid = 1U;
    }
    else
    {
        s_logical_position = FLAP_POSITION_INVALID;
        s_position_valid = 0U;
    }
}

uint8_t PositionSensing_GetPosition(uint8_t *pos_out)
{
    /* SWE-REQ-019: Provide current logical position if valid */
    if ((s_position_valid != 0U) && (pos_out != NULL))
    {
        *pos_out = s_logical_position;
        return 1U;
    }
    return 0U;
}

uint8_t PositionSensing_IsValid(void)
{
    /* SWE-REQ-017: Flag for position validity */
    return s_position_valid;
}