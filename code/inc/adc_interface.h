#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H
#include <stdint.h>

void ADC_Interface_Init(void);
uint8_t ADC_Interface_GetPosition(void);
uint16_t ADC_Interface_GetRaw(void);

#endif // ADC_INTERFACE_H
