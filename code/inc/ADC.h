#ifndef ADC_H
#define ADC_H
#include <stdint.h>
void ADC_Init(void);
void ADC_Process(void);
uint16_t ADC_GetValue(void);
#endif
