#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include <stdint.h>

void ADCInterface_Init(void);
void ADCInterface_StartConversion(void);
uint16_t ADCInterface_GetLastValue(void);
uint8_t ADCInterface_GetPosition(void);

#endif // ADC_INTERFACE_H
