#include "flap_manager.h"
#include "adc_manager.h"
#include "motor_control.h"
#include <stdint.h>

#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5
// ADC boundaries for positions 0-5, for demonstration
static const uint16_t adc_limits[6] = {100, 600, 1100, 1700, 2300, 2900};
static volatile int current_flap = -1;
static volatile int target_flap = -1;

void FLAP_Init(void)
{
    current_flap = FLAP_MapADC(ADC_Read());
    target_flap = current_flap;
}

// Return logical pos 0..5 or -1 if not mapped
int FLAP_MapADC(uint16_t value)
{
    for (int i = FLAP_POS_MIN; i <= FLAP_POS_MAX; ++i)
    {
        if (value < adc_limits[i]) return i;
    }
    return FLAP_POS_MAX;
}

int FLAP_GetCurrent(void) { return current_flap; }
int FLAP_GetTarget(void) { return target_flap; }

void FLAP_SetTarget(int position)
{
    if (position >= FLAP_POS_MIN && position <= FLAP_POS_MAX)
        target_flap = position;
}

void FLAP_Process(void)
{
    int adc = ADC_Read();
    current_flap = FLAP_MapADC(adc);
    if (target_flap > current_flap)
    {
        MOTOR_Run(MOTOR_DIR_CW);
    }
    else if (target_flap < current_flap)
    {
        MOTOR_Run(MOTOR_DIR_CCW);
    }
    else
    {
        MOTOR_Stop();
    }
}
