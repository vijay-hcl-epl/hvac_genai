#include "adc_manager.h"
#include "stm32f4xx_hal.h"
extern ADC_HandleTypeDef hadc1;
void ADC_Init(void)
{
    // Configure hadc1 in STM32Cube
}
uint16_t ADC_Read(void)
{
    uint16_t value = 0;
    HAL_ADC_Start(&hadc1);
    (void)HAL_ADC_PollForConversion(&hadc1, 10);
    if ((hadc1.Instance->SR & ADC_SR_EOC) != 0)
    {
        value = (uint16_t)HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Stop(&hadc1);
    return value;
}
