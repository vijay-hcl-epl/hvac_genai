#include "SignalIfManager.h"
#include "HAL.h"
// Example ADC mapping table
static const uint16_t adc_ranges[6][2] = {
    {0, 100}, {101, 600}, {601, 1200}, {1201, 1800}, {1801, 2400}, {2401, 3000}
};
static uint8_t last_position = 0U;
SignalStatus SignalIfManager_Update(uint16_t adc_value)
{
    for(uint8_t i=0; i<6; i++) {
        if(adc_value >= adc_ranges[i][0] && adc_value <= adc_ranges[i][1]) {
            last_position = i;
            SignalIfManager_SetLED(i);
            return SIG_OK;
        }
    }
    return SIG_ADC_OUT_OF_RANGE;
}
void SignalIfManager_Init(void)
{
    last_position = 0U;
}
uint8_t SignalIfManager_GetPosition(void)
{
    return last_position;
}
void SignalIfManager_SetLED(uint8_t pos)
{
    HAL_SetGreenLED(pos);
}
void SignalIfManager_StopMotor(void)
{
    HAL_StopMotor();
}
