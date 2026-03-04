#include "ADC.h"
#include "ErrorHandler.h"
static uint16_t adc_val = 0;
void ADC_Init(void) { adc_val = 0; }
void ADC_Process(void) { /* Acquire from hardware in real system */ }
uint16_t ADC_GetValue(void) { return adc_val; }
